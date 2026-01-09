#!/usr/bin/env python3
from PIL import Image, ImageDraw, ImageFont
import os

# Create 64x64 image
img = Image.new('RGBA', (64, 64), (0, 0, 0, 0))
draw = ImageDraw.Draw(img)

# Draw purple circle
draw.ellipse([8, 8, 56, 56], fill=(187, 134, 252))

# Draw dollar sign (simplified - using a circle instead of text)
draw.ellipse([24, 24, 40, 40], fill=(0, 0, 0))

# Save
img.save('docs/icon.png')
print("Icon created: docs/icon.png")
