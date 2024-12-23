import cv2
import json
import numpy as np

# Paths
config_path = 'regions.json'  # The regions JSON file

# Load the regions from the JSON file
with open(config_path, 'r') as f:
    regions = json.load(f)

# Create an empty canvas (black image)
canvas_height = 1920  # Adjust the height of the canvas
canvas_width = 1080  # Adjust the width of the canvas
canvas = np.zeros((canvas_height, canvas_width, 3), dtype=np.uint8)  # Black canvas

# Define colors for each lane (you can adjust the colors)
colors = {"upper_lane": (0, 0, 255),  # Red
          "left_lane": (0, 255, 0),   # Green
          "right_lane": (255, 0, 0)}  # Blue

# Draw the regions (polygons) on the empty canvas
for lane, coords in regions.items():
    if coords:  # Check if there are coordinates for the lane
        points = [(x, y) for x, y in coords]
        cv2.fillPoly(canvas, [np.array(points)], color=colors[lane])  # Fill the lane with color

# Display the canvas with restored lane areas
cv2.imshow("Lane Areas on Canvas", canvas)

# Optionally, save the restored image to a new file
output_image_path = 'restored_lane_areas_canvas.jpg'
cv2.imwrite(output_image_path, canvas)

# Wait for any key to close the displayed image
cv2.waitKey(0)
cv2.destroyAllWindows()
