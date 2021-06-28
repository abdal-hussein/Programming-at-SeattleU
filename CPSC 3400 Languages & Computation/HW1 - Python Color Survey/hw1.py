""" Justin Thoreson
Course:   CPSC3400
File:     hw1.py
Date due: 04-11-2021

This program takes the results of a color survey, where each person surveyed
provided their first, second, and third favorite colors, and processes them.
An list of colors in order of most first place votes can be generate.
The color scores of each color can be calculated.
The first place votes of a specified color can be retrieved.
A dictionary containing the colors and their respective votes can be viewed.
"""

import sys


def process_file(file_name):
    """ Takes a file containing a survey of colors and returns
  a dictionary with all the colors as keys and the number of first, second
  and third place votes as their values (tuple)
  
  :param: name of the file containing the survey
  :return: dictionary of colors and their votes
  """
    file = open(file_name, 'r')
    lines = file.readlines()
    file.close()

    # Populate dictionary with colors and their votes
    color_votes = {}
    for line in lines:
        for i, color in enumerate(line.split()):
            if color not in color_votes:
                color_votes[color] = [0, 0, 0]
            color_votes[color][i] += 1

    for color in color_votes:
        color_votes[color] = tuple(color_votes[color])
    return color_votes


def get_first_place_votes(color_survey, color):
    """ Takes a dictionary containing the results of a color survey and returns
  the number of first place votes of a specified color.

  :param: dictionary containing colors and their votes
  :param: a specified color (string)
  :return: the number of first place votes of the specified color
  """
    return color_survey[color][0] if color in color_survey else color + ' not found'


def create_favorite_color_list(color_survey):
    """ Generates a list of the top rated colors in primary order of first place
  votes, secondary order of second place votes, tertiary order of third place
  votes, and quaternary order of alphabetical order.

  :param: dictionary containing colors and their votes
  :return: an ordered list of colors excluding those with zero first place votes
  """
    # Generate list of colors ordered by first place votes
    favorite_colors = [color for color in color_survey.items() if color[1][0] != 0]
    favorite_colors = sorted(favorite_colors, key=lambda tup: tup[1][0])
    favorite_colors.reverse()

    # Secondary and tertiary ordering of second and third place votes
    for i in range(len(favorite_colors) - 1):
        if favorite_colors[i][1][0] == favorite_colors[i + 1][1][0]:
            if favorite_colors[i][1][1] < favorite_colors[i + 1][1][1]:
                swap(favorite_colors, i, i + 1)
            elif favorite_colors[i][1][1] == favorite_colors[i + 1][1][1]:
                if favorite_colors[i][1][2] < favorite_colors[i + 1][1][2]:
                    swap(favorite_colors, i, i + 1)

    # Quaternary ordering by alphabetical order
    for i in range(len(favorite_colors) - 1):
        if favorite_colors[i][1] == favorite_colors[i + 1][1]:
            if favorite_colors[i][0] > favorite_colors[i + 1][0]:
                swap(favorite_colors, i, i + 1)

    # Remove votes from list. List only contains names of colors in order
    for i in range(len(favorite_colors)):
        favorite_colors[i] = favorite_colors[i][0]
    return favorite_colors


def swap(colors, color1, color2):
    temp = colors[color1]
    colors[color1] = colors[color2]
    colors[color2] = temp


def create_color_score_dict(color_survey):
    """ Calculates the color scores of each color in the survey dictionary.
  The color score is the sum of first place votes times three, second
  place votes times two, and third place votes.

  :param: dictionary of colors and their votes
  :return: dictionary containing colors and their color scores
  """
    color_scores = {}
    for color in color_survey.items():
        color_scores[color[0]] = (3 * color[1][0]) + (2 * color[1][1]) + color[1][2]
    return color_scores


def print_dictionary(colors_dict):
    """ Prints the key value pairs of a dictionary.
  :param: dictionary containing colors and their votes
  """
    for color in sorted(colors_dict.items()):
        print(color[0] + ':', color[1])


""" Driver Code """

# Process survey in file
file_name = sys.argv[1]
color_survey = process_file(file_name)
print_dictionary(color_survey)

# Blue & Green 1st place votes
first_place_votes = get_first_place_votes(color_survey, 'blue')
print(first_place_votes)
first_place_votes = get_first_place_votes(color_survey, 'green')
print(first_place_votes)

# Colors ordered by vote
favorite_colors = create_favorite_color_list(color_survey)
print(favorite_colors)

# Calculate color scores
color_scores = create_color_score_dict(color_survey)
print_dictionary(color_scores)
