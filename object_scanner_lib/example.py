import sys
import object_scanner

# Create an ObjectScanner instance
scanner = object_scanner.ObjectScanner(17915)  # Replace with an actual process ID

# Attach to the process
if scanner.attach():
    print("Process attached successfully")

    # TODO: Reconstruct objects from memory regions
    obj = scanner.reconstruct_objects()
    if obj:
        print("Reconstructed object:", obj)
else:
    print("Failed to attach to the process.")
    sys.exit(0)


