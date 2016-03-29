# -*- coding: utf-8 -*-
from project import app
from bottle import template,static_file, request,  redirect
import bottle
import json
import string, os, sys

userdict={}
downlist={
		"1":u"产品手册","2":u"代码评审","3":u"功能测试","4":u"回归测试",
		"5":u"外部测试","6":u"学习","7":u"外部支持","8":u"性能测试","9":u"测试调试",
		"10":u"用例设计","11":u"系统测试","12":u"编程自测","13":u"设计文档","14":u"设计评审",
		"15":u"评估立项","16":u"说明文档","17":u"内部支持","18":u"部门相关","19":u"配置管理文档",
		"20":u"需求分析","21":u"会议","22":u"培训","23":u"指导","24":u"请假","25":u"其他",
		"26":u"节假日","28":u"单元测试","29":u"功能预研","30":u"概要/详细设计","31":u"编码实现"}

namelist={
		"74":u"石磊"
		}

def get_userdict(str):
	users = []
	for i in str.split("}"):
		user_dict = {}
		flag="no"
		for j in i.split(", "):		
			if j.find('"username":')!=-1:
				flag="ok"
				user_dict['username'] = j.split(': ')[1].strip('"')
			if j.find('"workload":')!=-1:
				user_dict['workload'] = j.split(': ')[1].strip('"')
			if j.find('"update":')!=-1:
				user_dict['update'] = j.split(': ')[1].strip('"')
			if j.find('"project":')!=-1:
				user_dict['project'] = j.split(': ')[1].strip('"')
			if j.find('"link":')!=-1:
				user_dict['link'] = j.split(': ')[1].strip('"')
			if j.find('"branch":')!=-1:
				user_dict['branch'] = j.split(': ')[1].strip('"')
			if j.find('"shortsha1":')!=-1:
				user_dict['shortsha1'] = j.split(': ')[1].strip('"')
			if j.find('"commit":')!=-1:
				user_dict['commit'] = j.split(': ')[1].strip('"')
			if j.find('"worktype":')!=-1:
				user_dict['worktype'] = j.split(': ')[1].strip('"')
		if flag=="ok":
			users.append(user_dict)
	return users

def get_dict(id):
	filename="./pre_report/"+id+".json"
	file = open(filename,'r')
	users=[]
 	for eachline in file:
 		line=eachline.strip().decode('utf-8')
 		line=line.strip(',')
 		userlist=json.loads(line)
 		if userlist["worktype"]=="RD":
 		 	userlist["worktype"]="12"
 		elif userlist["worktype"]=="SP":
 			userlist["worktype"]="17"
 		users.append(userlist)
 	return users
    	
def get_old_item(udict,sha):
	for i in range(len(udict)):
		if udict[i]['shortsha1']==sha:
			return i
		else:
			pass

@app.route('/im_file', method=['GET', 'POST'])
def im_file():
	if request.method == 'POST':
		uploadfile=request.files.get('fileInput')
		uploadfile.save('pre_report',overwrite=True)
		id = request.forms.get('uid')
	redirect('/init/%s' % id)
		
@app.route('/')
def index():
	return template('index.html',namelist=namelist)

@app.route('/init/<id>')
def init(id):
    global userdict
    userdict[id]=get_dict(id)
    if id in namelist:
    	return template('weeknote.html',id=id,name=namelist[id],dlist=downlist)
    else:
    	return template('weeknote.html',id=id,name='unknownUser',dlist=downlist)

@app.route('/all_submit/<id>')
def all_submit(id):
	newfile="./pre_report/"+id+".json"
	global userdict
	f=open(newfile,'w')
	for i in range(len(userdict[id])):
		outstr=json.dumps(userdict[id][i])
		f.write(outstr.strip().encode('utf-8') + '\n')	
	f.close()
	del userdict[id]	
	return '更新提交成功！<a href="/weeknote/%s">查看</a>' % id
	
@app.route('/weeknote/<id>', method=['GET', 'POST'])
def weeknote(id):
    	global userdict
    	if id not in userdict:
    		if id in namelist:
    			userdict[id]=get_dict(id)
    		else:
    			userdict[id]={}
        
   	if request.method == 'POST':
		op = request.forms.get('op')
		shortsha1 = request.forms.get('id')
		if op =="modify":
			item=get_old_item(userdict[id],shortsha1)
			userdict[id][item]['project'] = request.forms.get('project')
			userdict[id][item]['branch'] = request.forms.get('branch')
			userdict[id][item]['update'] = request.forms.get('date')
			userdict[id][item]['worktype'] = request.forms.get('type')
			userdict[id][item]['commit'] = request.forms.get('commit')
			userdict[id][item]['workload'] = request.forms.get('workload')
		elif op == "create":
			item=len(userdict[id])
			ulist={}
			ulist['project'] = request.forms.get('project')	
			ulist['project'] = request.forms.get('project')
			ulist['branch'] = request.forms.get('branch')
			ulist['update'] = request.forms.get('update')
			ulist['worktype'] = request.forms.get('worktype')
			ulist['commit'] = request.forms.get('commit')
			ulist['workload'] = request.forms.get('workload')
			if id=="74":
				ulist['username']="石磊（软件）"
			else:	
				ulist['username'] =namelist[id]
			ulist['link'] ="none"
			ulist['shortsha1']= ("sha%d" % item)
			userdict[id].append(ulist)		
		elif op == "delete":
			item=get_old_item(userdict[id],shortsha1)
			userdict[id].remove(userdict[id][item])
	#return template('weeknote.html',id=id,name=u'huqiming')
	if id in namelist:
		return template('weeknote.html',id=id,name=namelist[id],dlist=downlist)
	else: 
		return template('weeknote.html',id=id,name='unknownUser',dlist=downlist)
@app.route('/weeknote/list')
def list():
    id=request.query.userId
    global userdict
    if id not in userdict:
    	if id in namelist:
    		userdict[id]=get_dict(id)
    	else:
			userdict[id]={}
        

    print userdict[id]
    value = json.dumps(userdict[id])
    print value
    return value
