#!/bin/bash
echo "object: coke" > /home/wth/Desktop/Server/Server/static/detect_result.txt
rostopic echo -c /recognized_object_array | grep -m1 confidence >> /home/wth/Desktop/Server/Server/static/detect_result.txt
rostopic echo -c /recognized_object_array | grep -m1 -A8 position >> /home/wth/Desktop/Server/Server/static/detect_result.txt
 


