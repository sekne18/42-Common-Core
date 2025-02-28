import sys

def process_obj_file(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            parts = line.split()
            if not parts:
                continue
            
            if parts[0] == 'v':  # Keep vertex lines as they are
                outfile.write(line)
            elif parts[0] == 'f':  # Process face lines
                # Extract vertex indices only (remove normal/UV indices)
                vertex_indices = [p.split('/')[0] for p in parts[1:]]
                
                # Triangulate if necessary
                if len(vertex_indices) == 3:
                    outfile.write(f"f {' '.join(vertex_indices)}\n")
                else:
                    # Fan triangulation: (v1, v2, v3), (v1, v3, v4), (v1, v4, v5), ...
                    v1 = vertex_indices[0]
                    for i in range(1, len(vertex_indices) - 1):
                        outfile.write(f"f {v1} {vertex_indices[i]} {vertex_indices[i+1]}\n")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python process_obj.py input.obj output.obj")
    else:
        process_obj_file(sys.argv[1], sys.argv[2])
