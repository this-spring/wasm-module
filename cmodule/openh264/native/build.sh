###
 # @Author: xiuquanxu
 # @Company: kaochong
 # @Date: 2021-01-29 14:23:06
 # @LastEditors: xiuquanxu
 # @LastEditTime: 2021-01-29 14:50:57
### 
g++ h264.cc -I ./ -I ../codec/api/svc -L . -L ../ -lopenh264 -o h264.a