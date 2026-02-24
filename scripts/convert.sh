#!/bin/sh
# Usage: convert.sh input.txt [mazechart options] output.(ps|pdf|png|jpg)
# Runs: ./mazechart input.txt [args...] > tmp.jgr
#       jgraph < tmp.jgr > tmp.ps
#       then converts tmp.ps to output format based on extension.

set -e

if [ $# -lt 2 ]; then
    echo "usage: $0 <maze.txt> [mazechart options...] <output.ps|.pdf|.png|.jpg>"
    exit 1
fi

MAZECHART=./mazechart
INPUT=
OUTPUT=
EXTRA=

# Last arg is output file
eval OUTPUT=\$$#
# Rest: first is input, then optional mazechart options
i=1
for a in "$@"; do
    if [ $i -eq 1 ]; then
        INPUT="$a"
    elif [ $i -lt $# ]; then
        EXTRA="$EXTRA $a"
    fi
    i=$((i + 1))
done

if [ ! -x "$MAZECHART" ]; then
    echo "Error: $MAZECHART not found or not executable. Build with: make"
    exit 1
fi

if [ ! -f "$INPUT" ]; then
    echo "Error: input file not found: $INPUT"
    exit 1
fi

TMPJGR=$(mktemp -t mazechart.XXXXXX.jgr)
TMPPS=$(mktemp -t mazechart.XXXXXX.ps)
trap "rm -f $TMPJGR $TMPPS" EXIT

$MAZECHART "$INPUT" $EXTRA > "$TMPJGR" || { echo "mazechart failed"; exit 1; }

if ! command -v jgraph >/dev/null 2>&1; then
    echo "Error: jgraph not found. Install jgraph to convert maze to PostScript."
    echo "  macOS: jgraph is not in Homebrew; build from source. See JGRAPH.md in the project root."
    exit 1
fi
jgraph -P < "$TMPJGR" > "$TMPPS" || { echo "jgraph failed"; exit 1; }

ext=$(echo "$OUTPUT" | sed 's/.*\.//')
case "$ext" in
    ps)
        cp "$TMPPS" "$OUTPUT"
        ;;
    pdf)
        if ! command -v ps2pdf >/dev/null 2>&1; then
            echo "Error: ps2pdf not found. Install ghostscript for PDF output."
            exit 1
        fi
        ps2pdf "$TMPPS" "$OUTPUT"
        ;;
    png|jpg|jpeg)
        if ! command -v convert >/dev/null 2>&1; then
            echo "Error: convert (ImageMagick) not found. Install ImageMagick for PNG/JPG output."
            exit 1
        fi
        convert "$TMPPS" "$OUTPUT"
        ;;
    *)
        echo "Error: unknown output extension .$ext (use .ps, .pdf, .png, .jpg)"
        exit 1
        ;;
esac

echo "Wrote $OUTPUT"
