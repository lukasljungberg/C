import object_scanner

# Create an ObjectScanner instance
scanner = object_scanner.ObjectScanner(1234)  # Replace with an actual process ID

# Attach to the process
if scanner.attach():
    print("Process attached successfully")

    # Get memory regions
    regions = scanner.get_memory_regions()
    print("Memory regions:", regions)

    # Reconstruct objects from memory regions
    obj = scanner.reconstruct_objects()
    if obj:
        print("Reconstructed object:", obj)
else:
    print("Failed to attach to the process.")

# Create a DynamicObject instance
dynamic_obj = object_scanner.DynamicObject()

# Add fields to the DynamicObject
dynamic_obj.add_field("field1", 42)  # Add an int field
dynamic_obj.add_field("field2", 3.14)  # Add a float field

# Retrieve fields from the DynamicObject
print("Field 1 (int):", dynamic_obj.get_field("field1"))
print("Field 2 (float):", dynamic_obj.get_field("field2"))

# Print all fields
dynamic_obj.print_fields()
