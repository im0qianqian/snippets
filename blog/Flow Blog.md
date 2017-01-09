# Flow Blog

## **摘要**

当今，随着Internet的迅速普及以及网络技术的发展，人们的生活也越来越离不开这些东西，忙碌的生活，对着荧光屏幕的一整天，或许有效的记录可以在我们的生命中留下重要的点滴。这样的情况下，一个在线版的个人博客系统就显得非常有必要了。

本文论述了个人博客的特点，以及对其系统设计进行分析，并给出其功能以及数据库的设计。



### **关键词**

Python、MySQL、django、web应用程序开发、网站建设、CMS内容管理系统



## **系统概述**

### **背景**

> 博客最初始的名称是**Weblog**，由**web**和**log**两个单词组成，按照字面意思就为网络日记，后来喜欢新名词的人把这个词的发音故意改了一下，读成we blog，由此，blog这个词被创造了出来。
>
> Weblog就是在网络上发布和阅读的流水记录，通常称为“网络日志”。

简言之，Blog就是以网络作为载体，作者可以迅速便捷地发布自己的心得感想，并且可以及时有效的与他人进行交流。另外，一个Blog系统某种意义上来讲也是博主的个性化体现，我们可以通过不同的文章去了解作者，去感受作者想要描绘的思想。

一个Blog其实就是一个网站，它里面通常包含很多篇文章，所有的文章按照时间倒序排列，而读者则可以针对阅读过的文章发出评论与作者进行交流。许多Blog文章都是作者心之所想事情的发表，或者针对某件事情的记录，又或是一些成功的经验。



### **名称**

**命名为Flow的原因**

- 文章归档形如流水线的设计
- 更快、更简洁的流水式发布
- min_cost_max_flow





### **作用**

- 个人的自由表达与发布
- 知识的过滤与积累
- 深度交流沟通的网络新方式

博客，之所以公开在网络上，就是因为他不等同于私人日记，博客的概念肯定要比日记大很多，它不仅仅要记录关于自己的点点滴滴，还注重提供的内容能否帮助到别人。



## **系统设计**

### **系统需求分析**

#### **简述**

我们都希望有一个自己的博客网站，因为它可以用来记录我们生活的点点滴滴，也可以分享一些实践乐趣、成功经验。博客是公开的，大家都可以看到我们的文章，同时也都可以通过留言评论与博主进行交流，共同进步。

于是Flow Blog诞生了。



#### **系统目标**

**前台**

- 简约、快速、响应式设计
- 可阅读文章并对其进行评论
- 可通过分类或标签对文章进行过滤
- 实现友情链接页面
- 实现文章归档页面
- 实现RSS阅读

**后台**

每一个用户都有**自己在系统中的权限**，而在满足权限的条件下，他可以

- 创建组，并且可以修改该组所持有的权限
- 添加用户，可对新添加的用户授权
- 发表文章，文章可设置为对外公开或对外隐藏
- 创建页面（首页侧边栏所有的全站链接）
- 添加友链（友情链接页面）
- 添加标签（一个文章可含有多个标签属性）
- 添加分类（一个文章只能在一个分类里面）
- 更新评论（对读者所评论的内容等做出修改）

**性能**

- **实用性**：旨在提高内容管理和发布的效率
- **先进性**：后台采用ajax技术进行异步刷新
- **便捷性**：无论身处何地，无论时间，只要接入Internet网络，便可以随时创建并发布自己的文章



#### **技术可行性**

对于在浏览器上运行的web程序来说，我们首先想到的应该是B/S架构，服务器进行处理并返回我们在浏览器上所进行的操作请求。因此，主要的编程即为服务器端的编程，结合关系型数据库，共同组成一个完整的博客系统。



### **数据库设计**

#### **实体集**

首先，系统应该包含前台与后台，前台负责展示文章，后台可以添加并修改文章，因此系统中必须要有**用户**存在。

支持多用户同时登陆并进行操作，每一个用户可操作的内容不同，因此便有了用户权限问题，为了方便同样权限的用户统一管理，我们引入了**组**的概念，管理员可以创建组并赋予组一定的**权限**，而在组中的用户便得到了这些权限，这有点类似于数据库中的角色。

作为博客系统，我们要能在其中发布自己的文章与页面，于是便派生出**文章、页面**这两个实体，一般情况下我们可以选择让这两者合并。

文章都应该有自己的分类、标签等属性，而读者则可以对已公开的文章进行**评论**，于是便有了**分类、标签、评论**三个实体。

既然一个博客在某种程度上可以体现我们的个性化程度，同时我们在阅览别人的博客时也为了方便，想保存他人的链接以备后用，友情链接是一个比较好的选择，我们可以通过它很快的进入到它所链接的页面，当然是我们已经添加的地址。由此，**链接**便是一个独立的实体。



| 实体              | 描述   |
| --------------- | ---- |
| auth_user       | 用户   |
| auth_group      | 组策略  |
| auth_permission | 权限表  |
| flow_page       | 页面   |
| flow_post       | 文章   |
| flow_category   | 文章分类 |
| flow_comment    | 评论   |
| flow_tag        | 文章标签 |
| flow_link       | 友情链接 |
| pyblog_log      | 日志审计 |



##### **auth_user**

| 字段名          | 类型       | 大小   | 默认值  | 允许为空  | 属性    | 说明         |
| ------------ | -------- | ---- | ---- | ----- | ----- | ---------- |
| id           | int      | 11   |      | False | 主键、自增 | 用户ID编号     |
| password     | varchar  | 128  |      | False |       | 用户密码（md5）  |
| last_login   | datetime | 6    |      | False |       | 用户最后一次登录时间 |
| is_superuser | tinyint  | 1    | 0    | False |       | 是否为管理员     |
| username     | varchar  | 150  |      | False | 唯一    | 用户登录名      |
| first_name   | varchar  | 30   | ''   | True  |       | 名          |
| last_name    | varchar  | 30   | ''   | True  |       | 姓          |
| email        | varchar  | 254  |      | False | 唯一    | 用户邮箱       |
| is_staff     | tinyint  | 1    | 0    | False |       | 是否拥有管理     |
| is_active    | tinyint  | 1    | 0    | False |       | 是否活跃       |
| date_joined  | datetime | 6    |      | False |       | 用户注册时间     |



##### **auth_group**

| 字段名  | 类型      | 大小   | 默认值  | 允许为空  | 属性    | 说明    |
| ---- | ------- | ---- | ---- | ----- | ----- | ----- |
| id   | int     | 11   |      | False | 主键、自增 | 组ID编号 |
| name | varchar | 80   |      | False |       | 组名称   |



##### **auth_permission (static)**

| 字段名      | 类型      | 大小   | 默认值  | 允许为空  | 属性    | 说明     |
| -------- | ------- | ---- | ---- | ----- | ----- | ------ |
| id       | int     | 11   |      | False | 主键、自增 | 权限ID编号 |
| name     | varchar | 255  |      | False |       | 权限内容   |
| codename | varchar | 100  |      | False |       | 权限别名   |



##### **flow_page**

| 字段名      | 类型       | 大小   | 默认值  | 允许为空  | 属性    | 说明       |
| -------- | -------- | ---- | ---- | ----- | ----- | -------- |
| id       | int      | 11   |      | False | 主键、自增 | 页面ID编号   |
| title    | varchar  | 80   |      | False |       | 页面标题     |
| content  | longtext |      | ''   | True  |       | 页面内容     |
| alias    | varchar  | 80   |      | False | 唯一    | 页面别名     |
| created  | datetime | 6    |      | False |       | 页面创建日期   |
| modified | datetime | 6    |      | False |       | 页面最后修改日期 |



##### **flow_post**

| 字段名      | 类型       | 大小   | 默认值  | 允许为空  | 属性    | 说明                        |
| -------- | -------- | ---- | ---- | ----- | ----- | ------------------------- |
| id       | int      | 11   |      | False | 主键、自增 | 文章ID编号                    |
| created  | datetime | 6    |      | False |       | 文章创建日期                    |
| modified | datetime | 6    |      | False |       | 文章最后修改日期                  |
| title    | varchar  | 80   |      | False |       | 文章标题                      |
| content  | longtext |      | ''   | True  |       | 文章内容                      |
| excerpt  | longtext |      | ''   | True  |       | 文章描述                      |
| status   | tinyint  | 1    | 0    | False |       | 是否隐藏{1:'public',0:'hide'} |
| password | varchar  | 80   | ''   | True  |       | 文章加密密码                    |
| alias    | varchar  | 80   |      | False | 唯一    | 文章别名                      |
| views    | int      | 10   | 0    | False |       | 文章浏览次数                    |
| image    | varchar  | 200  | ''   | True  |       | 文章特色图片url                 |



##### **flow_category**

| 字段名         | 类型       | 大小   | 默认值  | 允许为空  | 属性    | 说明     |
| ----------- | -------- | ---- | ---- | ----- | ----- | ------ |
| id          | int      | 11   |      | False | 主键、自增 | 分类ID编号 |
| title       | varchar  | 80   |      | False |       | 分类标题   |
| alias       | varchar  | 80   |      | False | 唯一    | 分类别名   |
| description | longtext |      | ''   | True  |       | 分类描述   |



##### **flow_comment**

| 字段名          | 类型       | 大小   | 默认值  | 允许为空  | 属性    | 说明         |
| ------------ | -------- | ---- | ---- | ----- | ----- | ---------- |
| id           | int      | 11   |      | False | 主键、自增 | 评论ID编号     |
| author       | varchar  | 30   |      | False |       | 评论者名称      |
| author_email | varchar  | 254  |      | False |       | 评论者email   |
| author_url   | varchar  | 200  | ''   | True  |       | 评论者url     |
| author_ip    | char     | 39   |      | False |       | 当前评论发出IP地址 |
| created      | datetime | 6    |      | False |       | 评论时间       |
| content      | longtext |      |      | False |       | 评论内容       |



##### **flow_tag**

| 字段名   | 类型      | 大小   | 默认值  | 允许为空  | 属性    | 说明     |
| ----- | ------- | ---- | ---- | ----- | ----- | ------ |
| id    | int     | 11   |      | False | 主键、自增 | 标签ID编号 |
| title | varchar | 80   |      | False |       | 标签名称   |
| alias | varchar | 80   |      | False | 唯一    | 标签别名   |



##### **flow_link**

| 字段名         | 类型       | 大小   | 默认值  | 允许为空  | 属性    | 说明     |
| ----------- | -------- | ---- | ---- | ----- | ----- | ------ |
| id          | int      | 11   |      | False | 主键、自增 | 链接ID编号 |
| title       | varchar  | 80   |      | False |       | 链接名称   |
| url         | varchar  | 200  |      | False |       | 链接地址   |
| description | longtext |      | ''   | True  |       | 链接描述   |
| image       | varchar  | 200  | ''   | True  |       | 链接特色图片 |



##### **pyblog_log**

| 字段名            | 类型       | 大小   | 默认值  | 允许为空  | 属性    | 说明     |
| -------------- | -------- | ---- | ---- | ----- | ----- | ------ |
| id             | int      | 11   |      | False | 主键、自增 | 日志ID编号 |
| action_time    | datetime | 6    |      | False |       | 记录时间   |
| change_message | longtext |      |      | False |       | 更改内容   |
| type           | varchar  | 20   |      | False |       | 更改类型   |



#### **联系集**

##### **auth_user_user_permissions**

对于每一个用户，他都有自己在系统中的权限，因此用户和权限之间便具有了联系，并且每个用户可以拥有多个权限，每个权限也可以被多个用户所拥有，由此可以得出这是一个多对多的联系。

**派生表**

| 字段名           | 类型   | 大小   |
| ------------- | ---- | ---- |
| id            | int  | 11   |
| user_id       | int  | 11   |
| permission_id | int  | 11   |



##### **auth_user_groups**

之前有过说明，我们引入了组的概念，每一个用户可以同时属于多个组，每一个组中也可以存在多个用户，于是，组与用户之间存在多对多的关系。

**派生表**

| 字段名      | 类型   | 大小   |
| -------- | ---- | ---- |
| id       | int  | 11   |
| user_id  | int  | 11   |
| group_id | int  | 11   |



##### **auth_group_permissions**

管理员可以创建一个组，并且对这个组赋予不同的权限，每个组可以同时拥有多个权限，而每一个权限也可以分配给多个组，于是，组与权限之间也是多对多的关系。

**派生表**

| 字段名           | 类型   | 大小   |
| ------------- | ---- | ---- |
| id            | int  | 11   |
| group_id      | int  | 11   |
| permission_id | int  | 11   |



##### **post_user**

对于文章与用户来说，每一个用户可以发表多篇文章，而每一篇文章的作者只有一个，因此，用户与文章是一对多的关系，其外键字段添加到文章实体中，参照用户id。



##### **post_category**

每一篇文章只能有一个分类，而每一个分类中可以有多篇文章，分类与文章也属于一对多的关系，外键字段添加到文章实体中，参照分类id。



##### **category_category**

我们所能想到的分类，某些时候可能会包含它的子分类，也就是分类与分类之间也存在这样的关系，因为每一个分类只可能会有一个父分类，而它却可以同时拥有多个子分类，所以分类与分类间属于一对多的关系。



##### **post_tag**

用户在发表文章的时候，可以为该文章添加多个标签属性，同时每一个标签下面可能会有多篇文章，于是，标签与文章之间存在多对多的关系。

**派生表**

| 字段名     | 类型   | 大小   |
| ------- | ---- | ---- |
| id      | int  | 11   |
| post_id | int  | 11   |
| tag_id  | int  | 11   |



##### **post_comment**

因为读者可以为一篇文章发表自己的评论，而每个评论只能对应一篇文章，因此，文章与评论之间存在一对多的关系，外键字段添加到评论实体中，参照文章id。



##### **comment_comment**

某些时候，其他一些读者在阅读文章的时候会看到该文章的所有评论，当然，他也可以对这些评论进行反驳或者回复，于是，每一条评论都含有了它的父评论，也就是目标评论，而直接回复给文章的评论我们可以给其默认一个值，作为程序约束，由此我们可以看出，评论与评论之间的关系也是属于一对多的，外键字段添加到评论实体中，参照评论id。



##### **pyblog_log**

通过触发器记录了系统中的一些敏感操作，比如文章创建、修改与删除。



#### **整体物理模型**

![img](http://img.blog.csdn.net/20170108162246243?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



### **网站设计**

**网站主要分为两部分：**

- 前台展示部分
- 后台管理部分



#### **系统架构**

基于B/S（browser/server）结构，用户所做的所有操作都可在浏览器上完成，而服务器则会对用户的不同操作返回不同的处理结果。



#### **系统开发软硬件环境**

- **操作系统：**Windows 10、Ubuntu 16.04
- **Web服务器：**Apache/Nginx
- **网络和硬件平台：**任何可以连接到Internet的PC设备
- **数据库：**MySQL 5.6
- **编程语言：**Python 3.5
- **后端框架：**django
- **界面、程序设计工具：**Pycharm 2016.3、Google Chrome 57、Firefox Developer Edition 等工具。



#### **系统运行环境**

- **操作系统：**Windows Vista及以上版本、Linux、Unix

- **数据库：**MySQL 5.6

- **web服务器：**Apache/Nginx

- **环境搭建需要：**

  - Python 3.5
  - django 1.10.4
  - markdown 2.6.7
  - bootstrap-admin 0.3.7.1
  - PyMySQL 0.7.9
  - pytz 2016.10

  ​

#### **数据库的选择**

常用的关系型数据库有**MySQL**与**SQL Server**，在这里我选择了MySQL，MySQL是一个开源的小型关系型数据库管理系统，目前它被广泛应用在Internet上的中小型网站中。



**使用MySQL的原因：**

- 它是一个真正的多用户、多线程的数据库管理系统
- 小巧、功能齐全
- 可运行在Windows/Linux/Uinx等多种操作系统平台
- 拥有非常灵活并且安全的权限和口令系统，当客户与MySQL服务器连接时，它们之间所有的口令传送会被加密
- 拥有一个非常快速而稳定的基于线程的内存分配系统，可以持续使用而不必担心其稳定性
- 强大的查询功能，支持查询的SELECT和WHERE语句的全部运算符和函数，并且可以在同一查询中混用来自不同数据库的表，从而使得查询变的快捷和方便



#### **功能模块**

##### **首页**

加载文章列表，所有公开的文章分页显示

```python
url(r'^$', views.home),
```

![img](http://img.blog.csdn.net/20170108173633990?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



##### **文章页**

通过访问链接中的id查询文章内容，并在服务器端渲染后返回

```python
url(r'^detail/(?P<id>\d+).html$', views.detail, name='detail'),
```

![img](http://img.blog.csdn.net/20170108173727444?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



##### **普通页面**

通过页面别名查询页面内容，渲染后返回数据

```python
url(r'^(?P<alias>\w+)$', views.post_meta, name="post_meta"),
```

![img](http://img.blog.csdn.net/20170108173745325?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



##### **友情链接页面**

查询当前所有存储的链接，并利用特定的模板渲染返回

```python
url(r'^links$', views.links, name='links'),
```

![img](http://img.blog.csdn.net/20170108173808794?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



##### **归档**

查询当前已有的所有分类，以及该分类下的文章，返回的页面中按分类分块

```python
url(r'^categories/?$', views.categories, name='categories'),
```

![img](http://img.blog.csdn.net/20170108173834539?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



##### **查找**

利用接收到的参数，对所有的文章进行查找，所查找的字段包含文章标题以及文章描述

```python
url(r'^search/$', views.blog_search, name='search'),
```

![img](http://img.blog.csdn.net/20170108174108887?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



##### **通过分类或标签对文章过滤**

分别查询某一标签或者某一分类中公开的文章并渲染返回

```python
url(r'^tag/(?P<tag>\w+)/?$', views.search_tag, name='search_tag'),
url(r'^category/(?P<category>\w+)/?$', views.category, name='category'),
```

![img](http://img.blog.csdn.net/20170108173934138?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



##### **Feed**

对目前已经存在的文章进行RSS模式处理返回

```python
url(r'^feed/?$', views.RSSFeed(), name="RSS"),
```

![img](http://img.blog.csdn.net/20170108173903231?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



#### **django 运行处理机制**

当访问url时，django会根据ROOT_URLCONF的设置来装载URLConf。

然后按顺序逐个匹配URLConf里的URLpatterns，如果找到则会调用相关联的视图函数，并把HttpRequest对象作为第一个参数(通常是request)。

最后该view函数负责返回一个HttpResponse对象，然后找到相应的模板渲染出最终的页面返回给客户端。

![img](http://img.blog.csdn.net/20170108184651069?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjg5NTQ2MDE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



## **总结**

本文主要从数据库设计方面，分析了一个博客系统的内部的实体联系，利用Python语言+django框架实现了基于B/S的博客系统。

在这一次的课程设计中，我进一步的认识到了数据库应用系统**设计**的重要性，更少的数据冗余对数据库设计来说真的非常重要，以前都是用别人开发的博客系统，曾经有过为自己写一个同样系统的打算，最终因为没有时间而搁置，而这一次的数据库课程设计，在完成课程设计的同时我也完成了很久之前计划的任务。

虽然整个系统中涉及到的算法不多，但是前端的层叠样式表的设计还是花费了很多时间。

另外，程序的实现过程比较简单，博客的浏览速度也挺快，但是整个系统中还是存在着一些不足：

- 文章的实体应该与页面实体合并 （因为编程方面困难所以拆开了，以后会重新编写这一部分）
- 文章含有密码字段，但是在系统中并没有真正用到 （以后考虑继续完善这一功能）
- 站点主题不可更改 （以后考虑加入模板机制，可在配置中自由更改站点主题）

同时我也体会到了各方面知识结合运用的重要性，当然我也会继续努力，并不断完善这一系统。



**项目链接：** [Flow Blog](https://github.com/im0qianqian/Flow-blog)

## **参考文献**

[1] 朱波，黄勇.内容管理实话实说[J].微电脑世界，2002(ZI):1-10.

[2] 覃国蓉.基于B/S架构的软件项目实训[M].海淀：电子工业出版社，2004:40.