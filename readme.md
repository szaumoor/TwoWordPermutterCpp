# TwoWordPermutter

## Introduction

This is a small utility to generate usernames by reading a file containing eligible words and finding all the possible combinations of two words with a limit of 14 characters, as that pertains to Call of Duty.

## Rules for permutations

Check names.txt for an explanation. In short, each word must be on a separate line. Lines that start with "//" are skipped. Words that end with "#" are considered "first-word-only", and those that end with "*" are "second-word-only".

## How to use

The executable accepts two arguments:

1. Path to the input file. Relative, or absolute. Required
2. Character limit. Optional, no limit by default. Added because games establish a hard limit for the length of usernames. Passing 0 is equivalent to limitless.
