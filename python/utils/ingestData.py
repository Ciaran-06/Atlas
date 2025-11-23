import os
from pathlib import Path
import pandas as pd # type : ignore
from datetime import datetime
import sys
import time
from concurrent.futures import ProcessPoolExecutor, as_completed

RAW_DIR = Path("../../data/raw")
OUT_DIR = Path("../../data/processed")


# ------------------------------
# PROGRESS BAR
# ------------------------------
def progress_bar(current, total, bar_len=40):
    frac = current / total
    filled = int(bar_len * frac)
    bar = "█" * filled + "-" * (bar_len - filled)
    percent = int(frac * 100)
    sys.stdout.write(f"\r|{bar}| {percent}%  ({current}/{total})")
    sys.stdout.flush()


# ------------------------------
# WORKER FUNCTION (runs in parallel)
# ------------------------------
def process_file(file_path):
    file_path = Path(file_path)
    df = pd.read_csv(file_path)

    if "Ticker" not in df.columns or "Date" not in df.columns:
        return f"❌ Skipped {file_path.name}: missing Ticker/Date columns"

    # Convert Date
    df["Date"] = pd.to_datetime(df["Date"], errors="coerce")
    df = df.dropna(subset=["Date"])

    # Add Year column
    df["Year"] = df["Date"].dt.year

    # Process each ticker/year
    for ticker, tdf in df.groupby("Ticker"):
        ticker_folder = OUT_DIR / ticker
        ticker_folder.mkdir(parents=True, exist_ok=True)

        for year, ydf in tdf.groupby("Year"):
            out_path = ticker_folder / f"{year}.parquet"
            ydf.to_parquet(out_path, engine="pyarrow")

    return f"Processed {file_path.name}"


# ------------------------------
# MAIN FUNCTION
# ------------------------------
def main():
    print("Starting parallel parquet generation...\n")

    csv_files = list(RAW_DIR.glob("*.csv"))
    total = len(csv_files)

    if total == 0:
        print("No CSV files found.")
        return

    # Parallel execution
    results = []
    completed = 0

    with ProcessPoolExecutor() as executor:
        futures = {executor.submit(process_file, f): f for f in csv_files}

        for future in as_completed(futures):
            completed += 1
            msg = future.result()
            results.append(msg)
            progress_bar(completed, total)

    print("\n\n🎉 Done! All files processed into Parquet.")
    for r in results:
        print(" -", r)


if __name__ == "__main__":
    main()
