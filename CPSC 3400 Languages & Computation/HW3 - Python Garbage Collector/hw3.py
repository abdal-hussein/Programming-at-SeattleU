""" Justin Thoreson
Course: CPSC 3400 Languages & Computation
File: hw3.py
Due: 02 May 2021

This program is meant to simulate a mark & sweep algorithm used for garbage
collection. Memory blocks that are marked are reachable through named pointers,
while the swept blocks are unreachable and will be reclaimed.
"""


import sys
import os


class EmptyFileError(Exception):
    pass


def mark_sweep(filename):
    """ Traces through the heap blocks and marks the ones that are accessible
    and sweeps the ones that are inaccessible and need to be reclaimed.

    The first line contains the number of heap blocks.
    The remaining lines contain two values separated by a comma. The first
    value is either a heap block or a named pointer, and the second value is
    the heap block that the first value points to.

    :param filename: Name of the input file
    :return: A dictionary of marked and swept values
    """

    with open(filename, 'r') as file:
        if os.stat(filename).st_size == 0:
            raise EmptyFileError

        # Get all heap blocks and their pointers
        heap = {}
        for place, line in enumerate(file.readlines()):
            if place == 0:
                num_blocks = int(line)
                continue

            # First value points to second value
            first, second = line.split(',')
            if first.isnumeric():
                if int(first) not in heap:
                    heap[int(first)] = []
                heap[int(first)].append(int(second))
            else:
                if first not in heap:
                    heap[first] = []
                heap[first].append(int(second))

        # Filter out root pointers
        roots = [root for root in heap.keys() if type(root) == str]

        # DFS to track all heap blocks that have ties to a root pointer
        marked_swept = {"marked": [], "swept": []}
        for root in roots:
            path = []                  # Track all marked blocks
            blocks_to_search = [root]  # Note all blocks to check
            blocks_searched = []       # Note all blocks searched to avoid looping

            # Find the path of the current root
            while len(blocks_to_search) != 0:
                current_block = blocks_to_search.pop()
                if current_block not in path:
                    path.append(current_block)

                # Track blocks pointed to by the current block
                if current_block in heap.keys():
                    for value in heap[current_block]:
                        if value not in blocks_searched:
                            blocks_to_search.append(value)

                blocks_searched.append(current_block)

            # Store all heap blocks marked excluding named pointers and duplicate marked nodes
            marked_swept["marked"] += [marked for marked in path
                                       if type(marked) == int and marked not in marked_swept["marked"]]

        # Sort marked nodes and get swept nodes
        marked_swept["marked"] = sorted(marked_swept["marked"])
        marked_swept["swept"] = [swept for swept in range(num_blocks) if swept not in marked_swept["marked"]]

    return marked_swept


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('ERROR: Program must take only one input file')
        print('Usage: python3 hw3.py FILE_NAME.ext')
        exit(1)

    filename = sys.argv[1]

    try:
        marked_swept = mark_sweep(filename)
    except FileNotFoundError:
        print('ERROR: File not found')
        exit(1)
    except EmptyFileError:
        print('ERROR: File is empty')
        exit(1)
    else:
        print("Marked nodes:", *marked_swept["marked"])
        print("Swept nodes:", *marked_swept["swept"])
