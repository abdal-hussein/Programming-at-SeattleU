""" Justin Thoreson
Course: CPSC 3400 Languages & Computation
File:   hw2.py
Date:   04-18-2021

The purpose of this program is to be a time processor. Given a file containing
times, this program can print a list of the times in the format: HH:MM AM/PM.
This program can also find the latest time provided, print the times in order
from earliest to latest occurrence, and calculate the time difference of each
time in the list given a target time. The target time is the first time in the
list.
"""

import sys
import os


class EmptyFileError(Exception):
    pass


class ImproperTimeError(Exception):
    pass


def create_time_list(filename):
    """ Creates a list of time contained in the file.
    In the list, a time is represented as a tuple.

    :param filename: name of the input file
    :return: list of time tuples
    """
    file = open(filename, 'r')
    if os.stat(filename).st_size == 0:
        raise EmptyFileError

    # Create time tuples. EX: 2 11 PM --> (2, 11, 'PM')
    times = [tuple(int(i) if i.isdigit() else i for i in line.split()) for line in file.readlines()]
    file.close()

    # Check for invalid times
    for time in times:
        if len(time) > 3 or len(time) < 3:
            raise ImproperTimeError
        elif type(time[0]) != int or type(time[1]) != int or type(time[2]) != str:
            raise ImproperTimeError
        elif time[0] < 0 or time[0] > 12:
            raise ImproperTimeError
        elif time[1] < 0 or time[1] > 59:
            raise ImproperTimeError
        elif not (time[2] == "AM" or time[2] == "PM"):
            raise ImproperTimeError

    return times


def time_compare_gen(time_list, target):
    """ Compares how far in the future each time in the list is from a
    provided target time.

    :param time_list: list of time tuples
    :param target: a single time tuple to compare the times to
    :return: yields how far each time in the list is from the target time
    """
    for time in time_list:
        # Equal times
        if time == target:
            yield 0, 0

        # Equal hours, but minutes and AM/PM are potentially unequal
        elif time[0] == target[0]:
            if time[1] == target[1]:
                yield 12, 0
            elif time[1] > target[1]:
                if time[2] != target[2]:
                    yield 12, time[1] - target[1]
                else:
                    yield 0, time[1] - target[1]
            else:
                if time[2] != target[2]:
                    yield 11, 60 - (target[1] - time[1])
                else:
                    yield 23, 60 - (target[1] - time[1])

        # Account for time at 12 and target not at 12
        elif time[0] == 12 and target[0] != 12:
            if time[2] == target[2]:
                if time[1] == target[1]:
                    yield 24 - target[0], 0
                elif time[1] > target[1]:
                    yield 24 - target[0], time[1] - target[1]
                else:
                    yield 23 - target[0], 60 - (target[1] - time[1])
            else:
                if time[1] == target[1]:
                    yield 12 - target[0], 0
                elif time[1] > target[1]:
                    yield 12 - target[0], time[1] - target[1]
                else:
                    yield 11 - target[0], 60 - (target[1] - time[1])

        # Account for time not at 12 and target at 12
        elif time[0] != 12 and target[0] == 12:
            if time[2] == target[2]:
                if time[1] == target[1]:
                    yield time[0], 0
                elif time[1] > target[1]:
                    yield time[0], time[1] - target[1]
                else:
                    yield time[0] - 1, 60 - (target[1] - time[1])
            else:
                if time[1] == target[1]:
                    yield 12 + time[0], 0
                elif time[1] > target[1]:
                    yield 12 + time[0], time[1] - target[1]
                else:
                    yield 11 + time[0], 60 - (target[1] - time[1])

        # Account for time hour value greater than target value
        elif time[0] > target[0]:
            if time[2] == target[2]:
                if time[1] == target[1]:
                    yield time[0] - target[0], 0
                elif time[1] > target[1]:
                    yield time[0] - target[0], time[1] - target[1]
                else:
                    yield time[0] - target[0] - 1, 60 - (target[1] - time[1])
            else:
                if time[1] == target[1]:
                    yield 12 + (time[0] - target[0]), 0
                elif time[1] > target[1]:
                    yield 12 + (time[0] - target[0]), time[1] - target[1]
                else:
                    yield 11 + (time[0] - target[0]), 60 - (target[1] - time[1])

        # Account for time hour value less than target value
        else:
            if time[2] == target[2]:
                if time[1] == target[1]:
                    yield 24 - (target[0] - time[0]), 0
                elif time[1] > target[1]:
                    yield 24 - (target[0] - time[0]), time[1] - target[1]
                else:
                    yield 23 - (target[0] - time[0]), 60 - (target[1] - time[1])
            else:
                if time[1] == target[1]:
                    yield 12 - (target[0] - time[0]), 0
                elif time[1] > target[1]:
                    yield 12 - (target[0] - time[0]), time[1] - target[1]
                else:
                    yield 11 - (target[0] - time[0]), 60 - (target[1] - time[1])


def get_latest_time(time_list):
    """ Retrieves the latest time in the time list

    :param time_list: a list of time tuples
    :return: the latest time in the list
    """
    # Get only PM times
    latest_times = [time for time in time_list if time[2] == 'PM']
    if not latest_times:
        # Check for AM times later than 12:00 AM
        latest_times = [time for time in time_list if time[0] != 12]
        if not latest_times:
            latest_times = time_list
    else:
        # Check for PM times later than 12:00 PM
        later_than_12 = False
        for time in latest_times:
            if time[0] != 12:
                later_than_12 = True
                break
        if later_than_12:
            latest_times = [time for time in latest_times if time[0] != 12]

    return max(latest_times)


def get_sorted_times(time_list):
    """ Sorts the times in the list from earliest to latest

    :param time_list: a list of time tuples
    :return: a sorted list of times from earliest to latest
    """
    sorted_times = sorted(time_list)                                # Order times numerically
    am_times = [time for time in sorted_times if time[2] == 'AM']   # Separate AM times ...
    pm_times = [time for time in sorted_times if time[2] == 'PM']   # from PM times
    sorted_times = [time for time in am_times if time[0] == 12]     # Append 12AM times first
    sorted_times += [time for time in am_times if time[0] != 12]    # Append remaining AM times
    sorted_times += [time for time in pm_times if time[0] == 12]    # Append 12PM times
    sorted_times += [time for time in pm_times if time[0] != 12]    # Append remaining PM times
    return sorted_times


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('ERROR: Program must take only one input file')
        print('Usage: python3 hw2.py TIME_FILE.txt')
        exit(1)

    # Create time list from file and handle exceptions
    filename = sys.argv[1]
    try:
        time_list = create_time_list(filename)
    except FileNotFoundError:
        print('ERROR: File not found')
        sys.exit(1)
    except EmptyFileError:
        print('ERROR: File is empty')
        sys.exit(1)
    except ImproperTimeError:
        print('ERROR: File contains an improper time')
        sys.exit(1)

    # Print times w/ proper format
    new_times = [str(time[0]) + ':'
                 + ('0' + str(time[1]) if time[1] < 10 else str(time[1])) + ' '
                 + time[2] for time in time_list
                 ]
    print(new_times)

    # Print latest time, then print times in ascending order
    print(get_latest_time(time_list))
    print(get_sorted_times(time_list))

    # Compare time differences with first time in the list as the target
    target = time_list[0]
    time_diffs = [time for time in time_compare_gen(time_list[:], target)]
    print(time_diffs)
