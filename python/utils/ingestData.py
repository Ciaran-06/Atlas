import os
from pathlib import Path
import pandas as pd # type: ignore
from datetime import datetime
import sys
import time

RAW_DIR = Path("../../data/raw")
OUT_DIR = Path("../../data/processed")

# ------------------------------
# Progress bar helper
# ------------------------------
def progress_bar(current, total, bar_length=40):
    fraction = current / total
    filled = int(bar_length * fraction)
    bar = "█" * filled + '-' * (bar_length - filled)
    percent = int(fraction * 100)
    sys.stdout.write(f"\r|{bar}| {percent}% ({current}/{total})")
    sys.stdout.flush()

# ------------------------------
# MAIN PROCESSING
# ------------------------------
def process():
    print("Starting Data Ingestion + Ticker/Year Split...\n")

    csv_files = list(RAW_DIR.glob("*.csv"))

    if not csv_files:
        print("No CSV files found.")
        return

    total_files = len(csv_files)

    for idx, file in enumerate(csv_files, 1):
        print(f"\nProcessing {file.name}")

        # Load file into pandas
        df = pd.read_csv(file)

        # Validate required columns
        if "Ticker" not in df.columns or "Date" not in df.columns:
            print(f"  ❌ Skipped {file.name}: missing Ticker or Date columns")
            continue

        # Convert Date → datetime
        df["Date"] = pd.to_datetime(df["Date"], errors="coerce")
        df = df.dropna(subset=["Date"])

        # Group by ticker
        for ticker, ticker_df in df.groupby("Ticker"):
            ticker_folder = OUT_DIR / ticker
            ticker_folder.mkdir(parents=True, exist_ok=True)

            # Group by year
            ticker_df["Year"] = ticker_df["Date"].dt.year

            for year, year_df in ticker_df.groupby("Year"):
                out_path = ticker_folder / f"{year}.csv"
                year_df.to_csv(out_path, index=False)

        # Update progress bar
        progress_bar(idx, total_files)
        time.sleep(0.05)  # tiny delay so bar visibly updates

    print("\n\n🎉 Done! All tickers split by year and saved.")


if __name__ == "__main__":
    process()
