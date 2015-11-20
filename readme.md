[xx xxxx] 6 bits indicating how many bits per value - n
to output for a node:
  if is a node:
    [0]
    recurse for left
    recurse for right
  else
    [1] + n bits for freq + n bits for value
