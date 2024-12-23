from PIL import Image
import json

# Load coordinates from the JSON file
with open('coordinates.json', 'r') as json_file:
    coordinates = json.load(json_file)

# Get the size of the image (assuming the size is known or same as original image)
width = 1920  # Replace with the actual width of your image
height = 1080  # Replace with the actual height of your image

# Create a new blank image (white background)
image = Image.new('RGB', (width, height), (255, 255, 255))  # white background
pixels = image.load()

# Fill the regions based on the coordinates from the JSON file
for (x, y) in coordinates["up"]:
    pixels[x, y] = (255, 0, 0)  # Red region
for (x, y) in coordinates["left"]:
    pixels[x, y] = (0, 255, 0)  # Green region
for (x, y) in coordinates["right"]:
    pixels[x, y] = (0, 0, 255)  # Blue region

# Save the new image as 'regions.jpg'
image.save('regions.jpg')
