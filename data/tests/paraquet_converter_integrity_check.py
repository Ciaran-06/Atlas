import polars as pl # type: ignore
from pathlib import Path

RAW_DIR = Path("../raw")
PROC_DIR = Path("../processed")

def test_ticker(ticker: str):
    csv_file = RAW_DIR / f"{ticker}.csv"
    ticker_dir = PROC_DIR / ticker

    print(f"\n=== Testing {ticker} ===")

    # Load raw
    raw = pl.read_csv(
        csv_file,
        try_parse_dates=True,
        schema_overrides={"Date": pl.Date}
    ).with_columns(
        pl.col("Date").dt.year().alias("Year")
    )

    # Load parquet files
    parquets = sorted(ticker_dir.glob("*.parquet"))
    if not parquets:
        print("❌ No parquet files found!")
        return

    dfs = [pl.read_parquet(f) for f in parquets]
    merged = pl.concat(dfs, how="vertical")

    # Row count
    print("✅ Row count matches" if len(raw) == len(merged)
          else f"❌ Row count mismatch: CSV={len(raw)}, PQ={len(merged)}")

    # Date range
    raw_range = (raw["Date"].min(), raw["Date"].max())
    pq_range = (merged["Date"].min(), merged["Date"].max())
    print("✅ Date range matches" if raw_range == pq_range
          else f"❌ Date range mismatch:\n CSV={raw_range}\n PQ={pq_range}")

    # Years
    if set(raw["Year"].unique()) == set(merged["Year"].unique()):
        print("✅ Year set matches")
    else:
        print("❌ Year mismatch")

    # Column checksums
    bad = []
    cols = ["Open", "High", "Low", "Close", "Adj Close", "Volume"]
    for c in cols:
        if raw[c].hash().sum() != merged[c].hash().sum():
            bad.append(c)

    print("✅ All numeric columns match"
          if not bad else f"❌ Column mismatches: {bad}")

    # Full equality test
    if raw.equals(merged):
        print("✅ PERFECT MATCH — all data identical")
    else:
        print("⚠️ Data differs (use checks above)")

if __name__ == "__main__":
    for t in [f.stem for f in RAW_DIR.glob("*.csv")]:
        test_ticker(t)
