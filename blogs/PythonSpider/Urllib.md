## Urllib

- read()
- readline()
- readlines()
- geturl()
- getheaders()
- getcode()

```python
import urllib.request

url = "http://www.baidu.com"

response = urllib.request.urlopen(url)

content = response.read().decode('utf-8')

fp = open('./baidu.html', 'w')
fp.write(content)
fp.close()

# 获取状态码
return_code = response.getcode()
print(return_code)
# 获取url
return_url = response.geturl()
print(return_url)
# 获取Headers
return_headers = response.getheaders()
print(return_headers)


print(content)
```

- 请求对象的定制，urllib.request.Request() 
- urllib.request.urlencode(0)
- cookie 
- token
- handle
- builder_open
- open









> Urllib:
>
> 1、设置 URL
>
> 2、获取Request连接对象
>
> 3、设置编码格式
>
> 4、获取数据
>
> 5、下载





## Xpath



- 路径查询
  - //
  - //
- 谓词查询
  - /li[@id]
  - /li[@id="l1"]
- 属性查询
  - //@class
- 模糊查询
- 内容查询
- 逻辑运算
- 