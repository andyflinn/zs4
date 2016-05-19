////////////////////////////////////////////////////////////////////////"+"

var zs4 = {
	zs4:{
		count:{
			props:function(o,tc){
				var ret = 0;
				for (var n in o){
					if (tc!=null){
						if (tc(o[n])==true)
							ret++;
					}
					else{
						ret++;
					}
				}
				return ret;
			},
		},
		connect:function(cb,u){
			var js = zs4.zs4;
			var is = js.is;
			var constant = js.constant;
			if(u==null)u=location.pathname;
			zs4.zs4.server.post(u,"load",function(r){
				var o = JSON.parse(r);
				if	(zs4.zs4.is.object(o)&&o.zs4!=null&&zs4.zs4.is.string(o.zs4.url)){
					var n = ('zs4.'+js.string.reverse.elements(location.hostname,'.')); 
					var a = location.pathname.split('/');
					for (var i = 0 ; i < a.length ; i++ ){if(a[i]!=''){n+=('.'+a[i]);}}
					var co = js.create(n);
					
					co.zs4.authorize=function(path){
						if	(js.string.end(path,'zs4.login.password')==true){
							//zs4.zs4.console.log('zs4.zs4.authorize(\''+path+'\') is true');
							return true;
						}
						
						if	(this.url == constant.URL.PUBLIC){
							if(		!is.zs4.object(zs4.me)
								||	zs4.me.zs4.url != constant.URL.ROOT
								||	js.string.start(path,'zs4.login')
								)
								return false;
						}
						
						if	(js.string.start(path,'zs4.')){
							if	(	js.string.end(path,'zs4.ver')==true
								||	js.string.end(path,'zs4.url')==true
								||	js.string.end(path,'zs4.am')==true
								||	js.string.end(path,'zs4.own')==true
								||	js.string.end(path,'zs4.err')==true
								||	js.string.end(path,'zs4.login.session')==true
								){
								//zs4.zs4.console.log('zs4.zs4.authorize(\''+path+'\') is (zs4-readonly) false');
								return false;
							}
							
							if (	is.zs4.path.operator(path)
								&&	(	js.string.end(path,'.op4')
									||	js.string.end(path,'.sq4')
									||	js.string.end(path,'.vl4')
									||	js.string.end(path,'.vm4')
									||	js.string.end(path,'.tp4')
									)
								)
								return false;
						}
						
						if (this.own==true)
							return true;
							
						if (this.am==true)
							return true;
							

						//zs4.zs4.console.log('zs4.zs4.authorize(\''+path+'\') is true (default)');
						return true;
					};
					co.zs4.booleans=function(){
						var a = [];
						this.values(a,this.object,'',is.boolean);
						return a;
					},
					co.zs4.connectChildren=function(){
						var o = this.object;
						
						if (	js.is.object(o.zs4)
							&&	js.is.boolean(o.zs4.am)
							&&	o.zs4.am==true
							&&	js.is.object(o.zs4.login)
							&&	js.is.string(o.zs4.login.session)
							&&	o.zs4.login.session!=''
							){
							js.console.log('zs4.me='+o.zs4.var);
							zs4.me = o;
						}
						
						for (var p in o){

							if (p=='zs4'){
								continue;
							}
							if (js.is.zs4.connection(o[p])){
								
								//js.console.log('connecting: '+o[p].zs4.url);
								// functions
								o[p].zs4.authorize=this.authorize;
								o[p].zs4.booleans=this.booleans;
								o[p].zs4.connectChildren=this.connectChildren;
								o[p].zs4.getTransform=this.getTransform;
								o[p].zs4.numbers=this.numbers;
								o[p].zs4.objects=this.objects;
								o[p].zs4.setTransform=this.setTransform;
								o[p].zs4.strings=this.strings;
								o[p].zs4.trimChildren=this.trimChildren;
								o[p].zs4.trimFeature=this.trimFeature;
								o[p].zs4.values=this.values;

								// data properties
								o[p].zs4.object=o[p];
								o[p].zs4.var=(this.var+'.'+p);
								o[p].zs4.zs4=zs4.zs4;
								
								// link descendants....
								o[p].zs4.connectChildren();
							}
						}
					};
					co.zs4.getTransform=function(o,cb){
						js.console.log(o);
						var r = js.copy.object.properties(o,this.object);
						this.connectChildren();
						this.trimChildren(this.object,o);
					};
					co.zs4.numbers=function(){
						var a = [];
						this.values(a,this.object,'',is.number);
						return a;
					},
					co.zs4.objects=function(){
						var a = [];
						this.values(a,this.object,'',is.object);
						return a;
					},
					co.zs4.setTransform=function(rqo,cb){
						var caDo = false;
						// basic validation of server request...
						if	(!js.is.object(rqo)){js.console.log('error: '+JSON.stringify(rqo)+' is not an object');return false;}
						if	(!rqo.hasOwnProperty('var')||!js.is.string(rqo.var)){js.console.log('error: '+JSON.stringify(rqo)+' has no var (string) property');return false;}
						if 	(is.property(this.object,rqo.var)==null||!rqo.hasOwnProperty('val')){
							if (true!=this.own){
								var a = rqo.var.split('.');
								var l = a.length;
								//if (l<1||a[0]=='zs4'){
								//	this.zs4.console.log('error: you cannot add or remove zs4 cpabilities.');
								//	return false;
								//}
								if (this.am!=true){
									this.zs4.console.log('error: you cannot add or remove properties');
									return false;
								}
							}
						}
						
						if	(is.property(zs4,'me.zs4.login.session')!=null)rqo.session = zs4.me.zs4.login.session;
						var ctx = this;
						zs4.zs4.server.post(this.url,rqo,function(r){
							var o = JSON.parse(r);
							if	(zs4.zs4.is.object(o)&&o.zs4!=null&&zs4.zs4.is.string(o.zs4.url))ctx.getTransform(o);
							if(cb!=null)return cb(o);
							return false;
						});
						return zs4.zs4.console.log((this.var+'.zs4.setTransform('+JSON.stringify(rqo)+')'));
					};
					co.zs4.strings=function(){
						var a = [];
						this.values(a,this.object,'',is.string);
						return a;
					},
					co.zs4.trimChildren=function(o,p){
						var js = zs4.zs4;
						//js.console.log('trimChildren('+o.zs4.var+')')
						for (var n in o){
							if (n=='zs4'){
								var a = js.feature.array;
								var l = a.length;
								for (var i = 0 ; i < l ; i++ ){
									this.trimFeature(o,p,a[i]);
								}
								continue;
							}
							
							if (!p.hasOwnProperty(n)){
								delete o[n];
								continue;
							}
							
							if (js.is.zs4.object(o[n])){
								if (js.is.zs4.object(p[n])&&js.is.function(o[n].zs4.trimChildren)){o[n].zs4.trimChildren(o[n],p[n]);}
								continue;
							}
							
							if (js.is.object(o[n])&&js.is.object(p[n])){
								js.trim.properties(o[n],p[n]);
							}
						}
					}
					co.zs4.trimFeature=function(o,p,n){
						if	(js.is.object(o.zs4[n])){
							if (js.is.object(p.zs4[n])){js.trim.properties(o.zs4[n],p.zs4[n]);}
							else{delete o.zs4[n]};
						}
						
					};
					co.zs4.values=function(a,o,p,tc){
						if	(js.string.end(p,'zs4.object')==true||js.string.end(p,'zs4.zs4')||is.zs4.path.operator(p))return;
						for (var n in o){
							var path=p;if (path==''){path=n;}else{path+=('.'+n);}
							if	(is.zs4.path.zs4(path))continue;
							if	(tc(o[n])){
								if	(is.object(o[n])){if(!is.zs4.path.zs4(path)){a.push(path);}}
								else{a.push(path);}
							}
							if (is.object(o[n])){
								if	(is.zs4.path.zs4(p))continue;
								this.values(a,o[n],path,tc);
								continue;
							}
						}
					},
					co.zs4.getTransform(o);
					
					// run bootstrap function, if supplied....
					if (is.property(co,'zs4.function.body')!=null&&!is.function(co.zs4.function.boot)){
						var body = co.zs4.function.body;
						if (zs4.zs4.is.string(co.zs4.function.body)&&body!=''){
							zs4.zs4.console.log('install function here...');
							var foo = Function.constructor(body);
							foo.call(co);
						}
					}
					else{
							zs4.zs4.console.log('no bootstrap function...');
					}
					
					}
				if(cb!=null){return cb(co)};
				return false;
			});
		},
		constant:{
			FEATURE:{
				LOGIN:'login',
			},
			URL:{
				PUBLIC:'/public/',
				ROOT:'/',
			},
			context:{
				boolean:{
				},
				string:{
					USER:'USER',
				},
				number:{
				},
			},
		},
		console:{
			active:true,
			on:function(){return(zs4.zs4.console.active=true);},
			off:function(){return(zs4.zs4.console.active=false);},
			log:function(s){if(zs4.zs4.console.active==true)console.log(s);return zs4.zs4.console.active;},
		},
		copy:{
			object:{
				properties:function(s,d){
					var js = zs4.zs4;
					for (var n in s){
						if(js.is.object(s[n])){
							if(!d.hasOwnProperty(n)){d[n]={};}
							js.copy.object.properties(s[n],d[n]);
							continue;
						}
						d[n]=s[n];
					}
					return d;
				},
			},
		},		
		create:function(p){
			var js = zs4.zs4;
			//js.console.log('js.create.object(\''+p+'\')');
			if	(!js.is.string(p)||p=='')return null;
			var a = p.split('.');
			var l = a.length;
			if (l<1||a[0]!='zs4')return null;
			var o = zs4;
			for (var i=1;i<l;i++){
				if	(!js.is.object(o[a[i]])){o[a[i]]={};}
				o=o[a[i]];
			}
			o.zs4 = {
				object:o,
				var:p,
				ver:0,
				zs4:zs4.zs4,
			};
			return o;
		},
		feature:{
			array:['child','get','html','js','link','login','set'],
			transform:{
				vm4:['constant','null','property'],
				bool:['and','equal','or'],
				array:['get','set'],
				and:{
					na:0,
					tp:'boolean',
				},
				equal:{
					na:2,
					tp:'boolean',
				},
				or:{
					na:0,
					tp:'boolean',
				},
				value:{
					na:1,
					tp:'',
				},
			},
		},
		html:{
			body:function(){
				return document.getElementsByTagName("body")[0]
			},
			connect:function(cb){
				var elem = zs4.html;
				
				zs4.zs4.connect(function(conn){
					//zs4.zs4.console.log(d);
					
					elem.zs4.tabs();
					
					if	(zs4.html.zs4.content==null){					
						zs4.html.zs4.content = elem.zs4.tab.zs4.addPane('zs4');
					}
					
					zs4.html.zs4.set = function(obj){
						conn.zs4.setTransform(obj,zs4.html.zs4.refresh);
					};
					
					zs4.html.zs4.refresh = function(){
						//zs4.zs4.console.log('refreshing connection');
						
						zs4.html.zs4.content.zs4.value = conn;
						zs4.html.zs4.content.zs4.connection = conn;
						zs4.html.zs4.content.zs4.path = '';
						zs4.html.zs4.content.zs4.name = conn.zs4.var;

						zs4.html.zs4.content.zs4.refresh();
					};
					
					elem.zs4.refresh();
					
					if (cb!=null){cb(d);}
				});
			},
			edit:null,
			initialize:function(elem){
				var js = zs4.zs4;
				var is = js.is;
				var constant = js.constant;
				var html = js.html;
				
				zs4.html = elem;
				
				if	(!elem.hasOwnProperty('zs4')){
					elem.zs4 = {
						child:[],
						addremove:{
							refresh:function(htmlZs4){
								//var js = zs4.zs4;
								if	(	htmlZs4.value==null
									||	!is.object(htmlZs4.value)
									||	htmlZs4.connection==null
									||	htmlZs4.connection.zs4==null
									)return null;
								
								// create interface if it don't exist
								if (this.addProperty == null){
									// add functionality
									this.addProperty = this.create('zs4-add-property');
									this.addProperty.style.display = 'none';
									this.addProperty.zs4.toggleSpace = this.addProperty.zs4.toggler('');
									this.addProperty.zs4.addLabel = this.addProperty.zs4.create('zs4-add','add');
									this.addProperty.zs4.addLabel.zs4.htmlZs4 = htmlZs4;
									this.addProperty.zs4.addLabel.zs4.elemZs4 = this.addProperty.zs4;
									this.addProperty.zs4.addLabel.setAttribute('onclick','this.zs4.htmlZs4.addremove.addNow.call(this.zs4.htmlZs4,this.zs4.elemZs4)');
									this.addProperty.zs4.braceWrapper = this.addProperty.zs4.brace('(',')');
									this.addProperty.zs4.addBrace = this.addProperty.zs4.braceWrapper.zs4.elemBraceContent;
									
									this.addProperty.zs4.addType = this.addProperty.zs4.addBrace.zs4.create('select');
									this.addProperty.zs4.addTypeString = this.addProperty.zs4.addType.zs4.create('option');
									this.addProperty.zs4.addTypeString.value = this.addProperty.zs4.addTypeString.text = 'string';
									this.addProperty.zs4.addTypeBool = this.addProperty.zs4.addType.zs4.create('option');
									this.addProperty.zs4.addTypeBool.value = this.addProperty.zs4.addTypeBool.text = 'boolean';
									this.addProperty.zs4.addTypeNumber = this.addProperty.zs4.addType.zs4.create('option');
									this.addProperty.zs4.addTypeNumber.value = this.addProperty.zs4.addTypeNumber.text = 'number';
									this.addProperty.zs4.addTypeObject = this.addProperty.zs4.addType.zs4.create('option');
									this.addProperty.zs4.addTypeObject.value = this.addProperty.zs4.addTypeObject.text = 'object';
									
									this.addProperty.zs4.addFeature = this.addProperty.zs4.addBrace.zs4.create('select');
									
									this.addProperty.zs4.addComma = this.addProperty.zs4.addBrace.zs4.create('zs4-comma',',');
									
									this.addProperty.zs4.addName = this.addProperty.zs4.addBrace.zs4.create('input',',');
								}
								this.addProperty.zs4.addName.value = '';
								
								// display it?
								this.addremove.htmlZs4 = htmlZs4;
								this.addremove.am = htmlZs4.connection.zs4.am;
								this.addremove.own = htmlZs4.connection.zs4.own;
								
								//js.console.log(htmlZs4.connection.zs4.var+'.zs4:{path:\''+htmlZs4.path+'\',am:'+this.addremove.am+',own:'+this.addremove.own+'}');
								
								var amown = this.addremove.am;
								if (this.addremove.own==true)
									amown = true;
								//js.console.log(amown);
								if	(amown){
									//js.console.log('I own or am '+htmlZs4.connection.zs4.var+'.zs4:{path:\''+htmlZs4.path+'\',am:'+this.addremove.am+',own:'+this.addremove.own+'}');
									if (!js.string.start(htmlZs4.path,'zs4')){
										//js.console.log('configuring addProperty element');
										this.addProperty.style.display = 'block';
										this.addProperty.zs4.addType.style.display = 'inline';
										this.addProperty.zs4.addFeature.style.display = 'none';
										this.addProperty.zs4.addComma.style.display = 'inline';
										this.addProperty.zs4.addName.style.display = 'inline';
									}
									
									else if (this.addremove.own==true&&htmlZs4.path=='zs4'){
										var cnt = this.addremove.addFeatureCount.call(this,htmlZs4);
										//js.console.log('configuring addFeature element. '+cnt+' addable features...');
										if (cnt > 0 ){
											this.addProperty.style.display = 'block';
											this.addProperty.zs4.addType.style.display = 'none';
											this.addProperty.zs4.addFeature.style.display = 'inline';
											this.addProperty.zs4.addComma.style.display = 'none';
											this.addProperty.zs4.addName.style.display = 'none';
											
											this.addremove.addFeatureSelect.call(this,htmlZs4)
											
										}
										else{
											this.addProperty.style.display = 'none';
										}
									}
									else if (this.addremove.own==true&&is.zs4.path.operator(htmlZs4.path)&&is.zs4.operator(htmlZs4.value)){
											this.addProperty.style.display = 'inline';
											this.addProperty.zs4.addType.style.display = 'none';
											this.addProperty.zs4.addFeature.style.display = 'none';
											this.addProperty.zs4.addComma.style.display = 'none';
											this.addProperty.zs4.addName.style.display = 'none';
											
											//this.addremove.addTransformSelect.call(this,htmlZs4);
									}
									else{
										this.addProperty.style.display = 'none';
									}
								}
								else{
									this.addProperty.style.display = 'none';
								}
								
							},
							addNow:function(elemZs4){
								//zs4.zs4.console.log(this);
								//zs4.zs4.console.log(elemZs4);
								if (elemZs4.addName.style.display!='none'){
									if (!is.name(elemZs4.addName.value)){
										js.console.log('no valid property name supplied: \''+elemZs4.addName.value+'\'');
										return;
									}
									var nu = '';
									if (elemZs4.addType.value=='object')nu={};
									else if (elemZs4.addType.value=='boolean')nu=false;
									else if (elemZs4.addType.value=='number')nu=0;
									
									var p = this.path; if (p!='')p+='.';p+=elemZs4.addName.value;
									var rqo = {var:p,val:nu};
									
									//js.console.log(this.connection.zs4.var+'.zs4.setTransform('+JSON.stringify(rqo)+')');
									
									this.connection.zs4.setTransform(rqo,zs4.html.zs4.refresh);
								}
								else
								if (elemZs4.addFeature.style.display!='none'&&js.is.name(elemZs4.addFeature.value)){
									var p = (this.path+'.'+elemZs4.addFeature.value);
									this.connection.zs4.setTransform({var:p,val:{}},zs4.html.zs4.refresh);
								}
								else{
									this.connection.zs4.setTransform({var:(this.path+'.zs4add'),val:{}},zs4.html.zs4.refresh);
								}
							},
							addFeatureCount:function(htmlZs4){
								var r = 0;
								var objPublic = false;
								//if	(!is.object(zs4.me)||!is.object(zs4.me.zs4)||htmlZs4.value.url==constant.URL.PUBLIC)
								if	(htmlZs4.value.url==constant.URL.PUBLIC)
									objPublic = true;
								
								var a = js.feature.array;
								var l = a.length;
								for (var i = 0 ; i < l ; i++ ){
									if (objPublic==true&&a[i]==constant.FEATURE.LOGIN){continue;}
									if (is.property(htmlZs4.connection.zs4,a[i])==null&&is.object(zs4.me)&&is.object(zs4.me.zs4[a[i]])){r++;}
								}
								return r;
							},
							addFeatureSelect:function(htmlZs4){
								var objPublic = false;
								//if	(!is.object(zs4.me)||!is.object(zs4.me.zs4)||htmlZs4.value.url==constant.URL.PUBLIC)
								if	(htmlZs4.value.url==constant.URL.PUBLIC)
									objPublic = true;
								var sel = this.addProperty.zs4.addFeature;
								sel.innerHTML='';
								var a = js.feature.array;
								var l = a.length;
								for (var i = 0 ; i < l ; i++ ){
									if (objPublic==true&&a[i]==constant.FEATURE.LOGIN){continue;}
									if (is.property(htmlZs4.connection.zs4,a[i])==null&&is.object(zs4.me)&&is.object(zs4.me.zs4[a[i]])){
										var opt=sel.zs4.create('option',a[i]);
										opt.value=a[i];
									};
								}
								return sel;
							},
						},
						brace:function(open,close){
							var r = this.create('zs4-brace');
							r.zs4.elemBraceOpen = r.zs4.create(('zs4-brace-open'),open);
							r.zs4.elemBraceContent = r.zs4.create(('zs4-brace-content'));
							r.zs4.elemBraceClose = r.zs4.create(('zs4-brace-close'),close);
							return r;
						},
						clear:function(){
							var o = this.object;
							var a = this.child;
							var l = a.length;
							for (var i=0;i<l;i++){
								a[i].zs4.clear();
								o.removeChild(a[i]);
							}
							this.child=[];
						},
						create:function(nam,txt){
							var nu = document.createElement(nam);
							this.child.push(nu);
							nu.zs4 = {
								child:[],
								addremove:this.addremove,
								brace:this.brace,
								clear:this.clear,
								create:this.create,
								display:this.display,
								operatorMove:this.operatorMove,
								operatorRefresh:this.operatorRefresh,
								password:this.password,
								refresh:this.refresh,
								remove:this.remove,
								tabs:this.tabs,
								toggler:this.toggler,
								update:this.update,
								object:nu,
							};
							if	(txt!=null) nu.textContent = txt;
							this.object.appendChild(nu);
							return nu;
						},
						modify:function(){
						},
						operatorMove:function(by){
							if (this.isOpCode!=true)return;
							this.connection.zs4.setTransform({var:(this.path+'.sq4'),val:(this.value.sq4+by)},zs4.html.zs4.refresh);
						},
						operatorRefresh:function(){
							// Opcode UI data;
							var thisZs4 = this;
							if	(this.operatorUI==null){this.operatorUI={name:{}};}

							// conditional alteration of value?
							if (!this.operatorUI.hasOwnProperty('operatorSelect')){
								this.operatorUI.operatorString = this.operatorSpan.zs4.create('zs4-operator-string');
								this.operatorUI.operatorSelect = this.operatorSpan.zs4.create('select');
								this.operatorUI.operatorSelect.setAttribute('onchange','zs4.operatorSelectChange()');
								
								this.operatorUI.operatorNone = this.operatorUI.operatorSelect.zs4.create('option','');
								this.operatorUI.operatorNone.value = '';
								this.operatorUI.operatorIfAll = this.operatorUI.operatorSelect.zs4.create('option','ifAll');
								this.operatorUI.operatorIfAll.value = 'ifAll';
								this.operatorUI.operatorIfAny = this.operatorUI.operatorSelect.zs4.create('option','ifAny');
								this.operatorUI.operatorIfAny.value = 'ifAny';
								
								var sele = this.operatorUI.operatorSelect;
								this.operatorUI.operatorSelect.zs4.operatorSelectChange=function(){
									thisZs4.connection.zs4.setTransform({var:(thisZs4.path+'.op4'),val:sele.value},zs4.html.zs4.refresh);
								}
							}
							if (this.value.op4=='ifAll'){
								this.operatorUI.operatorSelect.value='ifAll';
								this.operatorUI.operatorString.textContent='ifAll';
							}
							else if (this.value.op4=='ifAny'){
								this.operatorUI.operatorSelect.value='ifAny';
								this.operatorUI.operatorString.textContent='ifAny';
							}
							else{
								this.operatorUI.operatorSelect.value='';
								this.operatorUI.operatorString.textContent='';
							}
							
							if (js.count.props(this.operatorObject,is.object)){
								this.operatorUI.operatorString.style.display='inline';
								this.operatorUI.operatorSelect.style.display='none';
							}
							else{
								this.operatorUI.operatorString.style.display='none';
								this.operatorUI.operatorSelect.style.display='inline';
							}
			
							// Opcode Name selector;
							if (!this.operatorUI.hasOwnProperty('operatorValueMode')){
								this.operatorUI.operatorValueMode = this.operatorSpan.zs4.create('select');
								this.operatorUI.operatorValueMode.setAttribute('onchange','zs4.operatorValueModeChange(this.value)');
								this.operatorUI.operatorValueMode.zs4.operatorValueModeChange = function(n){
									thisZs4.connection.zs4.setTransform({var:(thisZs4.path+'.vm4'),val:n},zs4.html.zs4.refresh);
								};
							}
							var a = js.feature.transform.vm4;
							var l = a.length;
							var vm4Name = this.operatorUI.operatorValueMode;
							for (var i = 0;i < l;i++){
								if(	(a[i]=='constant'||a[i]=='or'||a[i]=='equal'||a[i]=='and')
								&&	is.object(this.transformObject)
								)continue;
								if (!this.operatorUI.name.hasOwnProperty(a[i])){this.operatorUI.name[a[i]]=vm4Name.zs4.create('option',(a[i]));}
							}
							var vm4 = vm4Name.value = this.value.vm4;
							//js.console.log('value mode '+this.value.vm4+' '+this.value.tp4);
							if	(vm4 == 'property'){
								if (!this.operatorUI.hasOwnProperty('property')){
									this.operatorUI.property=this.operatorSpan.zs4.create('select');
									this.operatorUI.property.setAttribute('onchange','zs4.opValChange(this.value)');
									this.operatorUI.property.zs4.opValChange=function(v){
										thisZs4.connection.zs4.setTransform({var:(thisZs4.path+'.vl4'),val:v},zs4.html.zs4.refresh);
									}
								}
								var oVal = this.operatorUI.property;
								oVal.innerHTML='';
								
								var valArr = false;
								if (this.operatorObject.tp4=='string'){valArr = this.connection.zs4.strings();}
								else if (this.operatorObject.tp4=='boolean'){valArr = this.connection.zs4.booleans();}
								else if (this.operatorObject.tp4=='number'){valArr = this.connection.zs4.numbers();}
								else if (this.operatorObject.tp4=='object'){valArr = this.connection.zs4.objects();}
								
								if (is.array(valArr)&&valArr.length>0){
									var gotValue=false;
									var valLen = valArr.length;
									for (var i = 0 ; i < valLen ; i++){
										var valOpt = oVal.zs4.create('option',valArr[i]);
										valOpt.value = valArr[i];
										if	(this.value.vl4==valArr[i]){valOpt.selected=true;gotValue=true;}
									}
									//js.console.log('this.transformPath='+this.transformPath);
									if	(gotValue==false){this.value.vl4=this.transformPath;}
									this.operatorUI.property.value = this.value.vl4;
									this.operatorUI.property.style.display='inline';
								}
								else{
									//js.console.log('no props of type '+this.operatorObject.tp4);
									this.operatorUI.property.style.display='none';
								}
							}
							else if (this.operatorUI.hasOwnProperty('property')){
								this.operatorUI.property.style.display='none';
							}

							if 	(vm4 == 'constant'){
								if (this.operatorUI.hasOwnProperty('constantBoolean')){this.operatorUI.constantBoolean.style.display='none';}
								if (this.operatorUI.hasOwnProperty('constantNumber')){this.operatorUI.constantNumber.style.display='none';}
								if (this.operatorUI.hasOwnProperty('constantString')){this.operatorUI.constantString.style.display='none';}
								
								if	(this.operatorObject.tp4=='boolean'){
									if (!this.operatorUI.hasOwnProperty('constantBoolean')){
										this.operatorUI.constantBoolean=this.operatorSpan.zs4.create('select');
										this.operatorUI.constantBooleanFalse = this.operatorUI.constantBoolean.zs4.create('option','false');
										this.operatorUI.constantBooleanFalse.value = 'false';
										this.operatorUI.constantBooleanTrue = this.operatorUI.constantBoolean.zs4.create('option','true');
										this.operatorUI.constantBooleanTrue.value = 'true';
										this.operatorUI.constantBoolean.setAttribute('onchange','zs4.constantBooleanChange(this.value)');
										this.operatorUI.constantBoolean.zs4.constantBooleanChange=function(v){
											if (v=='true'){thisZs4.connection.zs4.setTransform({var:(thisZs4.path+'.vl4'),val:true},zs4.html.zs4.refresh);}
											else{thisZs4.connection.zs4.setTransform({var:(thisZs4.path+'.vl4'),val:false},zs4.html.zs4.refresh);}
										}
									}
									if (this.value.vl4==true){this.operatorUI.constantBoolean.value='true';}
									else{this.operatorUI.constantBoolean.value='false';}
									
									this.operatorUI.constantBoolean.style.display='inline';
								}
								else if (this.operatorObject.tp4=='number'){
									if (!this.operatorUI.hasOwnProperty('constantNumber')){
										this.operatorUI.constantNumber=this.operatorSpan.zs4.create('input');
										this.operatorUI.constantNumber.type='number';
										//this.operatorUI.constantNumber.setAttribute('onchange','zs4.constantNumberChange(this.value)');
										this.operatorUI.constantNumber.setAttribute('onblur','zs4.constantNumberChange(this.value)');
										this.operatorUI.constantNumber.zs4.constantNumberChange=function(v){
											var f = parseFloat(v);
											if (f==NaN)f=0.0;
											thisZs4.connection.zs4.setTransform({var:(thisZs4.path+'.vl4'),val:f},zs4.html.zs4.refresh);
										}

									}
									if (is.number(this.value.vl4))this.operatorUI.constantNumber.value = this.value.vl4;
									
									this.operatorUI.constantNumber.style.display='inline';
								}
								else if (this.operatorObject.tp4=='string'){
									if (!this.operatorUI.hasOwnProperty('constantString')){
										this.operatorUI.constantString=this.operatorSpan.zs4.create('input');
										this.operatorUI.constantString.setAttribute('onchange','zs4.constantNumberChange(this.value)');
										this.operatorUI.constantString.setAttribute('onblur','zs4.constantNumberChange(this.value)');
										this.operatorUI.constantString.zs4.constantNumberChange=function(v){
											thisZs4.connection.zs4.setTransform({var:(thisZs4.path+'.vl4'),val:v},zs4.html.zs4.refresh);
										}

									}
									if (is.string(this.value.vl4))this.operatorUI.constantString.value = this.value.vl4;
									
									this.operatorUI.constantString.style.display='inline';
								}
							}
							else{
								if (this.operatorUI.hasOwnProperty('constantBoolean')){this.operatorUI.constantBoolean.style.display='none';}
								if (this.operatorUI.hasOwnProperty('constantNumber')){this.operatorUI.constantNumber.style.display='none';}
								if (this.operatorUI.hasOwnProperty('constantString')){this.operatorUI.constantString.style.display='none';}
							}
							
						},
						password:function(){
							var pwd = this.create('input');
							pwd.type = 'password';
							pwd.size = 16;
							return pwd;
						},
						refresh:function(){

							if	(js.is.function(this.value)||js.is.array(this.value))
								return;

							var thisZs4 = this;
							//js.console.log('refreshing name:'+this.name+', path:'+this.path+', value:'+this.value);
							//js.console.log(this.value);

							if (this.toggleButton==null){
								this.toggleButton = this.toggler('+');
								this.toggleButton.zs4.block = this.block;
							}
							
							if	(this.allowEdit==null){
								this.allowEdit=true;
							}
							if (this.nameElement==null){
								this.moveUpElement = this.toggler();
								this.moveUpElement.innerHTML='&uarr;';
								this.moveUpElement.style.display='none';
								this.moveDownElement = this.toggler();
								this.moveDownElement.innerHTML='&darr;';
								this.moveDownElement.style.display='none';
								this.typeElement = this.create('zs4-value-type');
								this.nameElement = this.create('zs4-name',this.name);
								this.nameElement.zs4.value = this.value;
								this.nameElement.zs4.editObject = this.object;
								this.nameElement.setAttribute('onclick','zs4.click()');
								if (js.is.zs4.connection(this.value)){
									this.nameElement.setAttribute('class','zs4-connection');
								}
										
								
								this.nameElement.zs4.click=function(){
									thisZs4.update();
									
									if	(zs4.zs4.html.edit==this.editObject){
										zs4.zs4.html.edit = null;
									}
									else if	(this.editObject.zs4.allowEdit==true){
										zs4.zs4.html.edit = this.editObject;
										zs4.zs4.html.edit.focus();
									}
									zs4.html.zs4.refresh();
									//js.console.log(this.value);
								};
								
								this.nameRemove = this.create('zs4-name-remove','x');
								this.nameRemove.setAttribute('onclick','zs4.click()');
								this.nameRemove.zs4.click=function(){
									if (thisZs4.connection!=null&&js.is.string(thisZs4.path)){
										if (window.confirm('Really delete '+thisZs4.path+'?')){
											thisZs4.connection.zs4.setTransform({var:thisZs4.path},zs4.html.zs4.refresh);
										}
									}
								}
							}
							
							this.nameRemove.style.display = 'none';
							if	(this.connection!=null&&js.is.string(this.path)){
								this.allowEdit=this.connection.zs4.authorize(this.path);
								if (this.connection.zs4.own==true||this.connection.zs4.am==true){
									if (!js.string.start(this.path,'zs4')&&!js.is.zs4.connection(this.value)){
										this.nameRemove.style.display = 'inline';
									}
									else if (this.connection.zs4.own==true||this.connection.zs4.am==true){
									
										if (is.zs4.path.feature(this.path)){
											this.nameRemove.style.display = 'inline';
										}
										else if (is.zs4.path.operator(this.path)){
											if (is.object(this.value))this.nameRemove.style.display = 'inline';
										}
									}
								}
							}
							
							if (this.colonElement==null){
								this.colonElement = this.create('zs4-colon',':');
							}

							if	(js.is.object(this.value)){
								
								this.hasPath = is.string(this.path);
								
								this.isConnection = false; 
								if (is.zs4.connection(this.value)){
									this.isConnection = true;
									this.connection = this.value;
									this.path = '';
								}
								
								if (this.isTransform!=true)
									this.isTransform = false;
								if (this.hasPath==true&&this.connection!=null){
									this.transformObject = is.zs4.path.transform(this.connection,this.path);
									if (this.transformObject!=null){
										this.isTransform = true;
										var a = this.path.split('.');
										this.transformPath = js.string.replace.separator(a[2],'_','.');
									}
								}
								if (this.isOperator!=true)
									this.isOperator = false;
								if (this.hasPath==true&&is.zs4.path.operator(this.path)){
									this.isOperator = true;
									if (is.object(this.value)==true){
										this.operatorObject=this.value;
									}
								}

								if (this.isOpCode!=true)
									this.isOpCode = false;
								if (this.isTransform!=true&&this.isOperator==true)
								{
									this.isOpCode = true;
									
									this.moveUpElement.zs4.parentZs4 = this;
									this.moveUpElement.style.display = 'inline';
									this.moveUpElement.setAttribute('onclick','zs4.parentZs4.operatorMove(-15);');
									
									this.moveDownElement.zs4.parentZs4 = this;
									this.moveDownElement.style.display = 'inline';
									this.moveDownElement.setAttribute('onclick','zs4.parentZs4.operatorMove(15);');
								}	
								var isFeature = false;
									
								if	( this.content == null ){
									this.content = {
									expanded:false,
									object:{},
									};

									this.expressionContent = this.brace('(',')'); 
									this.expressionContent.setAttribute('class','zs4-expression');
									
									this.operatorContent = this.brace('{','}'); 
									this.operatorContent.setAttribute('class','zs4-curly-collapsed');
									this.operatorSpan = this.operatorContent.zs4.elemBraceContent;
									this.expandedContent = this.brace('{','}');
									this.expandedContent.setAttribute('class','zs4-curly-expanded');
									this.expandedContent.zs4.elemBraceContent.style.display = 'block';
									this.expandedContent.zs4.elemBraceContent.style.paddingLeft = '1em';
									this.expandedContent.zs4.elemBraceContent.style.marginLeft = '1em';
								}
								
								if	(this.isOperator==true){
									if	(this.isTransform==true){
										this.typeElement.textContent =(typeof(this.transformObject)+' ');
										this.typeElement.style.display='inline';
									}
									else if (this.operatorObject!=null){
										this.typeElement.textContent =(this.operatorObject.tp4+' ');
										this.typeElement.style.display='inline';
									}
									this.colonElement.style.display='none';
								}
								else {
									this.typeElement.style.display='none';
								}
							
								// add and remove interface....
								this.expandedContent.zs4.addremove.refresh.call(this.expandedContent.zs4.elemBraceContent.zs4,this);
								
								if (!js.is.function(this.toggle)){
									this.toggle = function(){
										if	(this.content.expanded == false){this.content.expanded = true;}
										else{this.content.expanded = false;}
										this.refresh();
									};
									this.toggleButton.zs4.link = this;
									this.toggleButton.setAttribute('onclick','zs4.link.toggle()');
								}
								
								if (this.content.expanded==true){
									
									var parentElement = this.expandedContent.zs4.elemBraceContent;
									// add new properties
									for ( var n in this.value ){
										if	(js.is.function(this.value[n]))continue;
										if	(this.path=='zs4'){
											// read-only connection info
											var isFeature = false;
											var a = js.feature.array;
											var l = a.length;
											for (var i = 0 ; i < l ; i++ ){
												if (n==a[i]){
													isFeature = true;
													break;
												}
											}
											
											if	(	n != 'ver'
												&&	n != 'url'
												&&	n != 'am'
												&&	n != 'own'
												&&	n != 'err'
												&&  isFeature != true
												)
												continue;
										}
										//if	(this.isTransform==true&&!is.object(this.value[n]))continue;
										
										if (is.zs4.connection(this.value)){
											this.connection = this.value;
											this.path = '';
										}
										
										var nPath = '';
										if (is.string(this.path)&&this.path!=''){nPath=this.path+'.'+n;}else{nPath=n;};
										
										if (!this.content.object.hasOwnProperty(n)){
											this.content.object[n]=parentElement.zs4.create(('zs4-'+n));
										}
										
										var ele = this.content.object[n];
										ele.zs4.value = this.value[n];
										ele.zs4.connection = this.connection;
										ele.zs4.path=nPath;
										ele.zs4.name=n;
										
										if (this.isOperator==true){
											ele.zs4.transformObject = this.transformObject;
											ele.zs4.transformPath = this.transformPath;
											ele.zs4.operatorObject = this.operatorObject;
										}

										ele.style.display='block';
										ele.zs4.refresh();
									}
									
									var opArr = [];
									// remove expired props
									for ( var n in this.content.object ){
										if (!this.value.hasOwnProperty(n)){
											parentElement.zs4.remove(this.content.object[n]);
											delete this.content.object[n];
										}
										else{
											opArr.push(this.content.object[n]);
										}
									}
	
									// sort operator members;
									if (this.isOperator==true){
										opArr.sort(function(a,b){
											//js.console.log('comparing '+a.zs4.name+' and '+b.zs4.name);
											if (a.zs4.isOperator!=true)return -1;
											if (b.zs4.isOperator!=true)return 1;
											return a.zs4.value.sq4 - b.zs4.value.sq4;
										});
										for (var i = 0 ; i < opArr.length ; i++ ){
											parentElement.removeChild(opArr[i]);
											parentElement.appendChild(opArr[i]);
										}
									}
	
									var lastElement = null;
									for ( var n in this.content.object ){
										lastElement = this.content.object[n];
										lastElement.zs4.commaElement.style.display='inline';	
									}
									if (lastElement != null)
										lastElement.zs4.commaElement.style.display='none';	
									
									
									this.operatorContent.style.display = 'none';
									this.expandedContent.style.display = 'inline';
									this.toggleButton.textContent = '-';
								}
								else{
									if	(this.isOperator==true){this.operatorContent.style.display = 'inline';this.operatorRefresh();}
									else{this.operatorContent.style.display = 'none';}
									this.expandedContent.style.display = 'none';
									this.toggleButton.textContent = '+';
								}
								
								if (this.isTransform==true){
									this.expressionContent.style.display = 'inline';
								}
								else{
									this.expressionContent.style.display = 'none';
								}
								//js.console.log(this.value);
							}
							else{ 
								this.toggleButton.textContent = '';
								if(js.is.string(this.value)){
									if (this.content == null){

										var braceWrapper = this.brace('\'','\'');
										var string = braceWrapper.zs4.elemBraceContent;

										this.content = string.zs4.create.call(string.zs4,'zs4-value',this.value);
										if (this.connection!=null&&this.path=='zs4.child.zs4.delete'){
											//js.console.log('create selector for deletable connections....'+this.connection.zs4.var+'.'+this.path);
											this.inputElement = string.zs4.create.call(string.zs4,'select');
										}
										else if (this.connection!=null&&this.connection.zs4.own==true&&is.zs4.path.vm4ode(this.path)){
											this.inputElement = string.zs4.create.call(string.zs4,'select');
											this.inputElement.zs4.context = thisZs4;
											this.inputElement.setAttribute('onchange','this.zs4.context.update()');
										}
										else{
											this.inputElement = string.zs4.create.call(string.zs4,'input');
										}
									}
								
									if	(this.connection!=null&&is.string(this.path)){
										if (this.path=='zs4.child.zs4.delete'){
											//js.console.log('create selector for deletable connections....'+this.connection.zs4.var+'.'+this.path);
											var sel = this.inputElement;sel.innerHTML='';
											var con = this.connection;
											var dft=sel.zs4.create('option');dft.value=null;
											
											for (var n in con){
												if (n=='zs4'||!js.is.zs4.connection(con[n]))continue;
												var opt=sel.zs4.create('option',n);opt.value=n;
											}
										}
										else if (is.zs4.path.vm4ode(this.path)){
											var sel = this.inputElement;sel.innerHTML='';
											var a = js.feature.transform.vm4;
											var l = a.length;
											for (var i = 0 ; i < l ; i++ ){
													var opt=sel.zs4.create('option',a[i]);
													opt.value=a[i];
											}
										}
									}	
									this.inputElement.value = this.value;
									if (this.object==js.html.edit){
										this.content.style.display='none';
										this.inputElement.style.display='inline';
									}
									else{
										this.content.style.display='inline';
										this.inputElement.style.display='none';
									}
								}else
								if(js.is.boolean(this.value)){
									if (this.content == null){
										this.content = this.create('zs4-value',this.value);
										this.inputElement = this.create('select');
										this.inputFalse = this.inputElement.zs4.create('option');
										this.inputFalse.value = false;
										this.inputFalse.text = false;
										this.inputTrue = this.inputElement.zs4.create('option');
										this.inputTrue.value = true;
										this.inputTrue.text = true;
										this.inputElement.zs4.context = thisZs4;
										this.inputElement.setAttribute('onchange','this.zs4.context.update()');
									}
									this.inputElement.value = this.value;
									if (this.object==zs4.zs4.html.edit){
										this.content.style.display='none';
										this.inputElement.style.display='inline';
									}
									else{
										this.content.style.display='inline';
										this.inputElement.style.display='none';
									}
								}else
								if(js.is.number(this.value)){
									if (this.content == null){
										this.content = this.create('zs4-value',this.value);
										this.inputElement = this.create('input');
										this.inputElement.type = 'number';
									}
									this.inputElement.value = this.value;
									if (this.object==zs4.zs4.html.edit){
										this.content.style.display='none';
										this.inputElement.style.display='inline';
									}
									else{
										this.content.style.display='inline';
										this.inputElement.style.display='none';
									}
								}
								this.content.textContent = this.value;
								this.content.zs4.namEle = this.nameElement;
								this.content.setAttribute('onclick','this.zs4.namEle.zs4.click()');
								
								if (this.allowEdit==true){
									this.nameElement.setAttribute('class','zs4-changeable');
									this.content.setAttribute('class','zs4-changeable');
								}
								else{
									this.nameElement.setAttribute('class','zs4-constant');
									this.content.setAttribute('class','zs4-constant');
								}

							}
							
							if	(this.transformToggle == null){
								this.tToggles = {};
								this.transformToggle = this.brace('t(',')');
								this.transformToggle.style.display='none';
							}
							if(this.connection!=null
							&&is.string(this.path)
							&&this.path!=''
							&&!js.string.start(this.path,'zs4')
							&&(this.connection.zs4.own==true||this.connection.zs4.am==true)
							){
								var pElem = this.transformToggle.zs4.elemBraceContent;
								
								var tArr = js.feature.transform.array;
								var tLen = tArr.length;
								var tCnt = 0;
								for (var tI = 0 ; tI < tLen ; tI++){
									if (null == is.property(zs4,'me.zs4.'+tArr[tI]))continue;
									var tPat = ('zs4.'+tArr[tI]+'.zs4add');
									var tObj = is.property(this.connection,tPat);
									//js.console.log(('testing for '+tPat));
									if (tObj==null){
										//js.console.log(tObj);
										if (!this.tToggles.hasOwnProperty(tArr[tI])){
											this.tToggles[tArr[tI]] = pElem.zs4.create(('zs4-transform-'+tArr[tI]),('('+tArr[tI]+')'));
											this.tToggles[tArr[tI]].setAttribute('class','zs4-transform-toggle');
											this.tToggles[tArr[tI]].setAttribute('onclick','zs4.click()');
											this.tToggles[tArr[tI]].zs4.tTogPath = tPat;
											this.tToggles[tArr[tI]].zs4.click=function(){
												js.console.log({var:this.tTogPath,val:{}});
												thisZs4.connection.zs4.setTransform({var:this.tTogPath,val:js.string.replace.separator(thisZs4.path,'.','_')},zs4.html.zs4.refresh);
											}
										}
										tCnt++;
										//js.console.log('show '+tPat);
										this.tToggles[tArr[tI]].style.display='inline';
									}
									else if (this.tToggles.hasOwnProperty(tArr[tI])){
										//js.console.log('[null]');
										//js.console.log('hide '+tPat);
										this.tToggles[tArr[tI]].style.display='none';
									}
								}
								
								if (tCnt>0){
									//js.console.log('show '+this.path+'....');
									this.transformToggle.style.display='inline';
								}
								else {
									//js.console.log('hide '+this.path+'....');
									this.transformToggle.style.display='none';
								}
							}
							else{
								this.transformToggle.style.display='none';
							}
							
							if	(this.commaElement==null){
								this.commaElement = this.create('zs4-comma',',');
								this.commaElement.style.display = 'none';
							}
						},
						remove:function(ele){
							this.object.removeChild(ele);
							var i=this.child.indexOf(ele);
							if(i>=0)this.child.splice(i,1);
						},
						tabs:function(){
							var tab = this.create('zs4-tab');
							this.tab = tab;
							this.tab.style.display = 'block';
							this.tab.zs4.pane = [];
							
							this.tab.zs4.header = this.tab.zs4.create.call(this.tab.zs4,'zs4-tab-header');
							this.tab.zs4.header.style.display = 'block';
							
							this.tab.zs4.content = this.tab.zs4.create.call(this.tab.zs4,'zs4-tab-content');
							this.tab.zs4.content.style.display = 'block';
							
							this.tab.zs4.addPane = function(name){
								var cont = tab.zs4.content.zs4.create('zs4-pane-content');
									cont.style.display = 'block'
								var head = tab.zs4.header.zs4.create('zs4-pane-header',name);
								head.zs4.tab = tab;
								head.zs4.click = function(){
									var pane = this.tab.zs4.pane;
									var l = pane.length;
									for ( var i = 0 ; i < l ; i++ ){
										if (pane[i].header == this.object){
											pane[i].header.setAttribute('class','zs4-selected');
											pane[i].content.zs4.refresh();
											pane[i].content.style.display = 'block';
											this.tab.zs4.currentPane = pane[i];
										}
										else{
											pane[i].header.setAttribute('class','zs4-idle');
											pane[i].content.style.display = 'none';
										}
									}
								};
								var paneSet = {header:head,content:cont};
								this.pane.push(paneSet);
								if	(tab.zs4.currentPane == null){tab.zs4.currentPane=paneSet;}
									
								return cont;
							}
							return tab;
						},
						toggler:function(txt){
							var togg = this.create('zs4-togglebutton',txt);
								togg.style.display = 'inline-block';
								togg.style.width = '1em';
								togg.style.height = '1em';
							return togg;
						},
						update:function(){
							var edObj = zs4.zs4.html.edit;
							if	(edObj != null){
								if (edObj.zs4!=null&&edObj.zs4.connection!=null&&edObj.zs4.inputElement!=null){
									//js.console.log('path:'+edObj.zs4.path+', value:'+edObj.zs4.value);
									if (js.is.boolean(edObj.zs4.value)){
										if	(edObj.zs4.inputElement.value=='true'){
											if	(edObj.zs4.value != true){
												edObj.zs4.connection.zs4.setTransform({var:edObj.zs4.path,val:true},zs4.html.zs4.refresh);
											}
										}
										else{
											if	(edObj.zs4.value != false){
												edObj.zs4.connection.zs4.setTransform({var:edObj.zs4.path,val:false},zs4.html.zs4.refresh);
											}
										}
									}
									else if (js.is.number(edObj.zs4.value)){
										var f = parseFloat(edObj.zs4.inputElement.value);
										if (f==NaN)f=0.0;
										edObj.zs4.connection.zs4.setTransform({var:edObj.zs4.path,val:f},zs4.html.zs4.refresh);
									}
									else{
										if	(edObj.zs4.value != edObj.zs4.inputElement.value){
											edObj.zs4.connection.zs4.setTransform({var:edObj.zs4.path,val:edObj.zs4.inputElement.value},zs4.html.zs4.refresh);
										}
									}
								}
							}
						},
						object:elem,
					};
				}
			},
			onload:function(){
				zs4.zs4.html.initialize(zs4.zs4.html.body());
				zs4.zs4.html.connect();
			},
		},
		is:{
			array:function(a){
				if	(a==null)return false;
				return (a instanceof Array);
			},
			boolean:function(b){
				if	(b==null)return false;
				if	(typeof(b)!='boolean')return false;
				return true;
			},
			function:function(f){
				if (f==null)return false;
				return (f instanceof Function);
			},
			name:function(n){
				if	(!zs4.zs4.is.string(n))return false;
				if	(n=="zs4")return true;
				var l=n.length;
				if	(l<1)return false;
				for (var i=0;i<l;i++){
					if(n.charAt(i)<'a'||n.charAt(i)>'z')return false;
				}
				return true;
			},
			number:function(b){
				if	(b==null)return false;
				if	(typeof(b)!='number')return false;
				return true;
			},
			object:function(o){
				if	(o==null)return false;
				if ((o instanceof Function)==true)return false;
				if	((o instanceof Array)==true)return false;
				if	(o instanceof Object)return true;
				return false;
			},
			property:function(o,p){
				if(!zs4.zs4.is.object(o)||!zs4.zs4.is.string(p))return null;
				var a = p.split('.');
				var l = a.length;
				var p = '';
				if (l<1)return null;
				if ((l>=2)&&(a[0]=='zs4')&&(a[1]=='zs4'))return null;
				//zs4.zs4.console.log('p.split().length='+l);
				for (var i = 0 ; i < l ; i++){
					if (p!='')p+='.'; p+=a[i];
					//zs4.zs4.console.log('checking o.'+p);
					if (!o.hasOwnProperty(a[i])){return null;}
					o=o[a[i]]; 
				}
				return o;
			},
			string:function(s){
				if	(s==null)return false;
				if	(typeof(s)!='string')return false;
				return true;
			},
			zs4:{
				connection:function(o){
					var js = zs4.zs4;
					if(	!js.is.zs4.object(o)
					||	!js.is.string(o.zs4.url)
					||	!js.is.number(o.zs4.ver)
					||	!js.is.boolean(o.zs4.am)
					||	!js.is.boolean(o.zs4.own)
					){
						return false;
					}
					return true;
				},
				object:function(o){
					var js = zs4.zs4;
					if(	!js.is.object(o)
					||	!js.is.object(o.zs4)
					){
						return false;
					}
					return true;
				},
				operator:function(o){
					if(!zs4.zs4.is.object(o))return false;
					if(	o.hasOwnProperty('sq4')
					&&	o.hasOwnProperty('vm4')
					)return true;
					return false;
				},
				path:{
					feature:function(p){
						var a = zs4.zs4.feature.array;
						var l = a.length;
						for (var i = 0 ; i < l ; i++ ){
							if (p==('zs4.'+a[i]))return true;
						}
						return false;
					},
					vm4ode:function(p){
						if (!zs4.zs4.string.end(p,'.vm4'))return false;
						
						var a = zs4.zs4.feature.transform.array;
						var l = a.length;
						for (var i = 0 ; i < l ; i++ ){
							if (zs4.zs4.string.start(p,('zs4.'+a[i]+'.')))return true;
						}
						return false;
					},
					operator:function(p){
						var a = zs4.zs4.feature.transform.array;
						var l = a.length;
						for (var i = 0 ; i < l ; i++ ){
							if (zs4.zs4.string.start(p,('zs4.'+a[i]+'.')))return true;
						}
						return false;
					},
					transform:function(conn,p){
						var js = zs4.zs4;
						var pa = p.split('.');
						if (pa.length!=3)return null;
						
						var a = js.feature.transform.array;
						var l = a.length;
						for (var i = 0 ; i < l ; i++ ){
							if (js.string.start(p,('zs4.'+a[i]+'.'))){
								return zs4.zs4.is.property(conn,js.string.replace.separator(pa[2],'_','.'));
							}
						}
				
						return null;
					},
					zs4:function(p){
						var js = zs4.zs4;
						if (!js.is.string(p)||p=='')return false;
						if (p.split('.').indexOf('zs4')>=0){
							//js.console.log(p+' contains zs4.');
							return true;
						}
						//js.console.log(p+' don\'t contain zs4.');
						return false;
					},
				},
			},
		},
		server:{
			ajax:function(u,cb){
				this.bindFunction=function(caller,o) {return function(){ return caller.apply(o,[o]);};};this.stateChange=function(o){if (this.request.readyState==4)this.cb(this.request.responseText);};this.getRequest=function(){if (window.ActiveXObject)return new ActiveXObject('Microsoft.XMLHTTP');else if(window.XMLHttpRequest)return new XMLHttpRequest();return false;};this.postBody=(arguments[2]||"");this.cb=cb;this.u=u;this.request=this.getRequest();if(this.request){var req=this.request;req.onreadystatechange=this.bindFunction(this.stateChange,this);if (this.postBody!==""){req.open("POST",u,true);req.setRequestHeader('Content-type','application/json');} else{req.open("GET",u,true);}req.send(this.postBody);}
			},
			get:function(u,cb){
				zs4.zs4.server.ajax(u,function(d){if(cb!=null)cb(d);});
				return ('this.server.ajax(\''+u+'\',cb)');
			},
			post:function(u,o,cb){
				zs4.zs4.server.ajax(u,function(d){if(cb!=null){cb(d);}else{zs4.zs4.console.log(zs4.response);}},JSON.stringify(o));
				return ('this.server.ajax(\''+u+'\',cb,'+JSON.stringify(o)+')');
			},
		},
		string:{
			end:function(s,e){
				if (s.substring((s.length - e.length),s.length)==e)return true;
				return false;
			},
			replace:{
				separator:function(str,old,nu){
					var r = '';
					var a = str.split(old);
					var l = a.length;
					for ( var i = 0 ; i < l ; i++ ){
						if (r!=''){r+=nu;}
						r+=a[i];
					}
					return r;
				},
			},
			reverse:{
				elements:function(str,sep){
					var a = str.split(sep);
					var l = a.length;
					var r = '';
					for (var i = l-1 ; i >= 0 ; i--){
						if (r!=''){r+=sep;}
						r+=a[i];
					}
					return r;
				}
			},
			start:function(s,e){
				if (s.substring(0,e.length)==e)return true;
				return false;
			},
		},
		trim:{
			properties:function(o,p){
				var js = zs4.zs4;
				for (var n in o){
					if (!p.hasOwnProperty(n)){delete o[n];continue;}					
					if (js.is.object(o[n])){js.trim.properties(o[n],p[n]);}
				}
				return o;
			},
		},
	},
};

