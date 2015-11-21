[xxxxxx] 6 bits indicating how many bits per frequency - n
[xxxxxx] 6 bits indicating how many bits per value - m
to output for a node:
  if it is a leaf:
    [1] + n bits for freq + m bits for value
  else
    [0]
    recurse for left
    recurse for right
