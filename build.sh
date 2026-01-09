#!/bin/bash
echo "Building Money Tracker..."

# Compile
g++ src/money_tracker.cpp -o money-tracker \
  -I/usr/include/qt6 \
  -lQt6Widgets \
  -lQt6Core \
  -lQt6Gui \
  -fPIC

if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    chmod +x money-tracker
    echo "Run with: ./money-tracker"
else
    echo "❌ Build failed!"
    exit 1
fi
