from PIL import Image
import json

# Open the image
image = Image.open('ref.jpg')  # Replace with the path to your image
pixels = image.load()

# Get the size of the image
width, height = image.size

# Initialize lists for coordinates of each region
upper_lane = []
left_lane = []
right_lane = []

# Loop through each pixel in the image and categorize by color
for y in range(height):
    for x in range(width):
        r, g, b = pixels[x, y]  # Get the RGB value of the pixel
        if r > 200 and g < 100 and b < 100:  # Red region (adjust threshold as needed)
            upper_lane.append((x, y))
        elif r < 100 and g > 200 and b < 100:  # Green region (adjust threshold as needed)
            left_lane.append((x, y))
        elif r < 100 and g < 100 and b > 200:  # Blue region (adjust threshold as needed)
            right_lane.append((x, y))

# Prepare the data for saving
coordinates = {
    "upper_lane": upper_lane,
    "left_lane": left_lane,
    "right_lane": right_lane
}

# Save the coordinates in a JSON file
with open('coordinates.json', 'w') as json_file:
    json.dump(coordinates, json_file)
