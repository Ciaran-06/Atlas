import os
from pathlib import Path
import polars as pl # type: ignore
from concurrent.futures import ProcessPoolExecutor, as_completed
from tqdm import tqdm # type: ignore
import sys
import logging

RAW_DIR = Path("../../data/raw")
OUT_DIR = Path("../../data/processed")
LOG_DIR = Path("../../data/logs/ingest.log")
# ----------------------------------------
# Logging Setup
# ----------------------------------------
logging.basicConfig(
    filename=LOG_DIR,
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s"
)
# ----------------------------------------
# PROCESS ONE FILE (Runs in parallel)
# ----------------------------------------
def process_file(file_path):
    file_path = Path(file_path)

    try:
        ticker = file_path.stem.upper()

        # Read CSV using Polars (FAST)
        df = pl.read_csv(
            file_path,
            try_parse_dates=True,
            dtypes={"Date": pl.Date},
        )

        if "Date" not in df.columns:
            return f"❌ {ticker}: No Date column"

        # Add missing ticker column
        df = df.with_columns(pl.lit(ticker).alias("Ticker"))

        # Extract year
        df = df.with_columns(
            pl.col("Date").dt.year().alias("Year")
        )

        # Output directory for this ticker
        ticker_dir = OUT_DIR / ticker.split(".")[0]
        ticker_dir.mkdir(parents=True, exist_ok=True)

        # Split by year and save fast Parquet files
        for year, ydf in df.group_by("Year"):
            year = year[0]
            out_file = ticker_dir / f"{year}.parquet"
            ydf.write_parquet(out_file)

        return f"✅ Processed {ticker}"

    except Exception as e:
        return f"❌ ERROR {file_path.name}: {e}"


# ----------------------------------------
# MAIN PIPELINE
# ----------------------------------------
def main():
    OUT_DIR.mkdir(parents=True, exist_ok=True)

    csv_files = list(RAW_DIR.glob("*.csv"))
    total = len(csv_files)

    if total == 0:
        print("No CSV files found.")
        sys.exit(1)

    print(f"🚀 Starting processing of {total} files...\n")

    results = []

    # Use all CPU cores for max speed
    with ProcessPoolExecutor() as executor:
        futures = {executor.submit(process_file, f): f for f in csv_files}

        for future in tqdm(as_completed(futures), total=total, desc="Progress"):
            msg = future.result()
            results.append(msg)
            logging.info(msg)

    print("\n🎉 DONE — All files processed!\n")
    for r in results:
        print(r)


if __name__ == "__main__":
    main()
