#!/bin/bash
# Install Money Tracker AppImage to system

APP="Money-Tracker-x86_64.AppImage"
DESKTOP_FILE="money-tracker.desktop"
ICON="money-tracker.png"

# Check if AppImage exists
if [ ! -f "$APP" ]; then
    echo "Error: $APP not found in current directory"
    exit 1
fi

# Copy AppImage to ~/.local/bin
mkdir -p ~/.local/bin
cp "$APP" ~/.local/bin/money-tracker
chmod +x ~/.local/bin/money-tracker

# Create desktop file
cat > ~/.local/share/applications/money-tracker.desktop << DESKTOP
[Desktop Entry]
Name=Money Tracker
Comment=Simple money tracking application
Exec=$HOME/.local/bin/money-tracker
Icon=money-tracker
Terminal=false
Type=Application
Categories=Utility;Finance;Office;
Keywords=money;tracker;finance;budget;
StartupNotify=true
DESKTOP

# Copy icon if available
if [ -f "docs/icon.png" ]; then
    mkdir -p ~/.local/share/icons/hicolor/64x64/apps
    cp docs/icon.png ~/.local/share/icons/hicolor/64x64/apps/money-tracker.png
fi

echo "✅ Money Tracker installed successfully!"
echo "   Run from terminal: ~/.local/bin/money-tracker"
echo "   Or find in your applications menu as 'Money Tracker'"
