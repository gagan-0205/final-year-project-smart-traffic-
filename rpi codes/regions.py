import cv2
import numpy as np
import json

# Load the image
image_path = 'ref.jpg'  # Update with the path to your image
image = cv2.imread(image_path)

# Define the colors and tolerance
tolerance = 20  # Adjust this value for more/less tolerance
colors = {
    "upper_lane": (0, 0, 255),  # Red in BGR
    "left_lane": (0, 255, 0),   # Green in BGR
    "right_lane": (255, 0, 0)   # Blue in BGR
}

# Dictionary to store the coordinates
regions = {}

# Detect each color and store pixel coordinates
for lane, color in colors.items():
    # Define the lower and upper bounds for the color
    lower_bound = np.clip(np.array(color) - tolerance, 0, 255)
    upper_bound = np.clip(np.array(color) + tolerance, 0, 255)
    
    # Create a mask for the specific color range
    mask = cv2.inRange(image, lower_bound, upper_bound)
    
    # Find non-zero pixel coordinates
    coordinates = cv2.findNonZero(mask)
    
    # Store the coordinates in a list
    if coordinates is not None:
        regions[lane] = [(int(point[0][0]), int(point[0][1])) for point in coordinates]
    else:
        regions[lane] = []

# Save the regions to a config file
config_path = 'regions.json'
with open(config_path, 'w') as f:
    json.dump(regions, f, indent=4)

print(f"Regions saved to {config_path}")
