require 'net/http'


str = Net::HTTP.get('baidu.com','/index.html')
puts str
