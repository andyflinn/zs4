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
		html:{
			body:function(){
				return document.getElementsByTagName("body")[0]
			},
			initialize:function(elem){
				var js = zs4.zs4;
				var is = js.is;
				var constant = js.constant;
				var html = js.html;
				
				zs4.html = elem;
				
				if	(!elem.hasOwnProperty('zs4')){
					elem.zs4 = {
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

