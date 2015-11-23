[xxxxxx] 6 bits indicating how many bits per value - n
to output for a node:
  if it is a leaf:
    [1] + m bits for value
  else
    [0]
    recurse for left
    recurse for right
