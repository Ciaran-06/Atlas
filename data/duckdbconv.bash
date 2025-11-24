#!/bin/bash

RAW_DIR=""
OUT_DIR="/path/to/parquet/files"

mkdir -p "$OUT_DIR"

for file in "$RAW_DIR"/*.csv; do
    filename=$(basename "$file" .csv)

    # extract ticker and year — adjust regex if needed
    ticker=$(echo "$filename" | cut -d'_' -f1)
    year=$(echo "$filename" | grep -oE '[0-9]{4}' | head -1)

    if [ -z "$year" ]; then
        echo "No year in filename $filename → skipping"
        continue
    fi

    outpath="$OUT_DIR/ticker=$ticker/year=$year"
    mkdir -p "$outpath"

    output_file="$outpath/${ticker}_${year}.parquet"

    echo "Converting $file → $output_file"

    duckdb -c "
        COPY (
            SELECT *
            FROM read_csv_auto('$file')
        ) TO '$output_file'
        (FORMAT PARQUET, COMPRESSION 'SNAPPY');
    "
done

echo "Done!"
