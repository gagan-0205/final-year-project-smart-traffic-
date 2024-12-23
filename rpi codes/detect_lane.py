import cv2
import json
from ultralytics import YOLO

# Paths
image_path = '1.jpg'  # The image to analyze
config_path = 'coordinates.json'  # The regions JSON file
yolo_model_path = 'yolov10n.pt'  # Path to YOLOv10n model

# Load regions
with open(config_path, 'r') as f:
    regions = json.load(f)

# Convert region coordinates to bounding boxes
def get_bounding_box(coords):
    """Get the bounding box for a list of pixel coordinates."""
    if not coords:
        return None
    x_coords = [x for x, y in coords]
    y_coords = [y for x, y in coords]
    return (min(x_coords), min(y_coords), max(x_coords), max(y_coords))

lane_bounding_boxes = {
    lane: get_bounding_box(coords) for lane, coords in regions.items()
}

# Load YOLO model
model = YOLO(yolo_model_path)

# Run YOLO on the image
results = model(image_path)

# Vehicle class IDs (adjust as per YOLOv10n class mapping)
vehicle_classes = [2, 5, 7]  # 2: Car, 5: Bus, 7: Truck (example IDs; check your model's mappings)

# Get detected vehicles
vehicles = []
for result in results:
    for box in result.boxes:
        if box.cls in vehicle_classes:  # Check if it's a vehicle
            x1, y1, x2, y2 = map(int, box.xyxy[0])  # Bounding box coordinates
            vehicles.append((x1, y1, x2, y2))

# Function to check bounding box overlap
def is_overlapping(box1, box2):
    """Check if two bounding boxes overlap."""
    if box1 is None or box2 is None:
        return False
    x1, y1, x2, y2 = box1
    x1_r, y1_r, x2_r, y2_r = box2
    return not (x2 < x1_r or x2_r < x1 or y2 < y1_r or y2_r < y1)

# Count vehicles in each lane
lane_vehicle_counts = {"upper_lane": 0, "left_lane": 0, "right_lane": 0}

for vehicle_box in vehicles:
    for lane, region_box in lane_bounding_boxes.items():
        if is_overlapping(vehicle_box, region_box):
            lane_vehicle_counts[lane] += 1

# Output results
for lane, count in lane_vehicle_counts.items():
    print(f"{count} vehicle(s) detected in {lane}.")
