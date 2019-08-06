#!/bin/sh

# Buld the test, then run it if build was successful

bazel build //assignments/dg:graph_test && bazel run //assignments/dg:graph_test
