#coding=utf-8
'''
Created on 2016年03月29日

@FileName: manage.py

@Description: (描述) 

@Site:  http://www.sugarguo.com/

@author: 'Sugarguo'

@version V1.0.0
'''

import os
import json
import time
from datetime import datetime

from flask import Flask, render_template, flash, redirect, url_for, request
from flask.ext.script import Manager
from flask.ext.sqlalchemy import SQLAlchemy
from flask.ext.bootstrap import Bootstrap
#from flask.ext.mysql import MySQL
from flask.ext.login import UserMixin
from flask.ext.wtf import Form
#from flask.ext.migrate import Migrate
from wtforms import StringField, PasswordField, TextAreaField, DateField, IntegerField, SelectField, SubmitField
from wtforms.validators import Required
from sqlalchemy.ext.declarative import declarative_base




basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] =\
	'mysql://root:chaochao520@127.0.0.1/weekly_report'
app.config['SQLALCHEMY_COMMIT_ON_TERADOWN'] = True
app.config['SECRET_KEY'] = 'hjkl;GHJKgH535463ghkjlHJKL'
app.debug = True

db = SQLAlchemy(app)
bootstrap = Bootstrap(app)
manager = Manager(app)

#migrate = Migrate(app, db) 

#manager.add_command('db', MigrateCommand)

userdict={}
downlist={
		"1":u"产品手册","2":u"代码评审","3":u"功能测试","4":u"回归测试",
		"5":u"外部测试","6":u"学习","7":u"外部支持","8":u"性能测试","9":u"测试调试",
		"10":u"用例设计","11":u"系统测试","12":u"编程自测","13":u"设计文档","14":u"设计评审",
		"15":u"评估立项","16":u"说明文档","17":u"内部支持","18":u"部门相关","19":u"配置管理文档",
		"20":u"需求分析","21":u"会议","22":u"培训","23":u"指导","24":u"请假","25":u"其他",
		"26":u"节假日","28":u"单元测试","29":u"功能预研","30":u"概要/详细设计","31":u"编码实现"
		}

namelist={
		"74":u"石磊"
		}

tempdict = {}


#Base = sqlalchemy.ext.declarative.declarative_base()
#Base = declarative_base()

class Recording(db.Model):
	__tablename__ = 'recordings'
	id = db.Column(db.Integer, primary_key = True)
	project = db.Column(db.String(128),unique = True, nullable = False) 
	branch = db.Column(db.String(128))
	endtime = db.Column(db.Date, nullable = False)
	worktype = db.Column(db.String(128))
	workload = db.Column(db.Integer)
	workcontent = db.Column(db.Text)
	
	#def re_dict(self):
	#	return "{project   branch   endtime    worktype   workload    workcontent}"
	
	#def re_dict(self):
	#	return _sa_instance_state;
	
	#def to_dict(self):
	#	return {c.name: getattr(self, c.name, None) for c in self.__table__.columns}
	
	

class User(UserMixin, db.Model):
	__tablename__ = 'users'
	id = db.Column(db.Integer, primary_key = True)
	username = db.Column(db.String(64), unique = True, index = True)
	password_hash = db.Column(db.String(128))

	@property
	def password(self):
		raise AttributeError('password is not a readable attribute')

	@password.setter
	def password(self, password):
		self.password_hash = generate_password_hash(password)

	def verify_password(self, password):
		return check_password_hash(self.password_hash, password)



class RecordForm(Form):
	project = StringField(u'主任务名', validators = [Required()])
	branch = StringField(u'子任务名')
	date = DateField(u'完成时间', validators = [Required()])
	worktype = SelectField(u'工作类型', validators = [Required()], choices=[
	        ('1', u'产品手册'),('2', u'代码评审'),('3', u'功能测试'),('4', u'回归测试'),('5', u'外部测试'),('6', u'学习'),('7', u'外部支持'),('8', u'性能测试'),('9', u'测试调试'),('10', u'用例设计'),('11', u'系统测试'),('12', u'编程自测'),('13', u'设计文档'),('14', u'设计评审'),('15', u'评估立项'),('16', u'说明文档'),('17', u'内部支持'),('18', u'部门相关'),('19', u'配置管理文档'),('20', u'需求分析'),('21', u'会议'),('22', u'培训'),('23', u'指导'),('24', u'请假'),('25', u'其他'),('26', u'节假日'),('28', u'单元测试'),('29', u'功能预研'),('30', u'概要/详细设计'),('31', u'编码实现')], default='1')
	workload = IntegerField(u'工作时间', validators = [Required()])
	commit_info = TextAreaField(u'工作详情')
	submit = SubmitField(u'确定')


class UserForm(Form):
	username = StringField(u'用户名', validators = [Required()])
	password = PasswordField(u'密码', validators = [Required()])
	submit = SubmitField(u'登陆')



@app.route('/')
@app.route('/index.html')
def index():
	#projectlist = Recording.query.filter_by().all()
	#for item in projectlist:
	#	item.worktype = downlist[item.worktype]
	#return '<h1>hello</h1>'
	return render_template('index.html', dlist = downlist)#,**locals())

@app.route('/test')
@app.route('/test.html')
def test():
	return render_template('test.html', **locals())

@app.route('/login', methods = ['GET', 'POST'])
@app.route('/login.html', methods = ['GET' , 'POST'])
def login():
	form = UserForm()
	if form.validate_on_submit():
		user = User.query.filter_by(username = form.username.data).first()
		if user is not None and user.verify_password(form.password.data):
			return redirect(request.args.get('next') or url_for('index'))
		flash(u'登陆出错，请检查后重试！')
	return render_template('login.html', **locals())



@app.route('/add', methods = ['GET', 'POST'])
def add():
	name = u'石磊'
	op = request.form.get('op')
	id = request.form.get('id')
   	if request.method == 'POST':
		print request.form.get('project')
		print request.form.get('branch')
		print request.form.get('endtime')
		print request.form.get('worktype')
		print request.form.get('workload')
		print request.form.get('workcontent')
		recordings = Recording(id = id,
							project=request.form.get('project'),
							branch = request.form.get('branch'),
							endtime = request.form.get('endtime'),
							worktype = request.form.get('worktype'),
							workload = request.form.get('workload'),
							workcontent = request.form.get('workcontent')
							)
		#db.session.merge(recordings)
		db.session.add(recordings)
		db.session.commit()
		flash(u'数据更新完毕')
		
		
		return redirect(url_for('index'))
	return render_template('index.html')# ,form=form)


@app.route('/update/<int:id>', methods = ['GET', 'POST'])
def update(id):
	name = u'石磊'
   	if request.method == 'POST':
		print request.form.get('project')
		print request.form.get('branch')
		print request.form.get('endtime')
		print request.form.get('worktype')
		print request.form.get('workload')
		print request.form.get('workcontent')
		return redirect(url_for('index'))
	return render_template('index.html')# ,form=form)





@app.route('/delete/<int:page>', methods = ['GET', 'POST'])
@app.route('/delete.html/<int:page>',methods = ['GET', 'POST'])
def delete(page):
	projectinfo = Recording.query.filter_by(id=page).first()
	if projectinfo is None:
		flash(u'数据删除出错！请检查后重试！')
	else:
		db.session.delete(projectinfo)
		db.session.commit()
	return redirect(url_for('index'))

@app.route('/weeknote', methods = ['GET', 'POST'])
@app.route('/weeknote.html',methods = ['GET', 'POST'])
def weeknote():
	dlist = Recording.query.filter_by().all()
	for item in dlist:
		item.worktype = downlist[item.worktype]
	#return '<h1>hello</h1>'
	return render_template('weeknote.html', **locals())


@app.route('/getinfo', methods = ['GET', 'POST'])
def getinfo():
	tempjson = "["
	#projectlist = Recording.query.filter_by(id = userid).all()
	projectlist = Recording.query.filter_by().all()
	#user = User.query.filter_by(username = form.username.data).first()
	for item in projectlist:
		item.workload = str(item.workload)
		#item.worktype = downlist[item.worktype]
		item.endtime = item.endtime.strftime("%Y-%m-%d")
		#time.strftime("%Y-%m-%d", time.localtime(item.endtime))
		tempdict = item.__dict__
		del tempdict["_sa_instance_state"]
		value = json.dumps(tempdict)
		tempjson += value + ","
	tempjson = tempjson[:-1] + "]"

	print tempjson
	return tempjson
	#return render_template('index.html', **locals())
	

if __name__ == '__main__':
    manager.run()
