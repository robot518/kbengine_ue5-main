# 效果视频
知乎演示视频：https://www.zhihu.com/zvideo/1652312603551576064
# kbengine_ue5

  kbengine source:https://github.com/kbengine/kbengine.git

1. 使用kbengine-main中提供的源文件修改并重新编译kbe相关代码

2. 调用new_assets.bat重新生成ue5版本的服务器

3. 修改本地数据库配置，kbengine\kbe\res\server\kbengine_defaults.xml或者kbengine\server_assets\res\server\kbengine.xml中覆盖默认配置,否则dbmgr连接数据库异常

4. 调用gensdk.bat生辰ue5版本插件

5. 编写插件中Scripts代码

6. 插件放到ue5工程中，.build.cs中引用模块，.uproject中关联插件

# mysql注意事项

  mysql8 安装时选择 Use Legacy Authentication Method,不使用caching_sha2_password 密码身份验证

  ProgramData\MySQL\MySQL Server 8.0\my.ini中[mysqld]下面加上skip_ssl

  net start mysql80

  mysql> use mysql;

  mysql> select user,host,plugin from user;//查看当前验证方式
  
  mysql> ALTER USER 'root'@'%' IDENTIFIED WITH mysql_native_password BY '123456';//修改验证方式
