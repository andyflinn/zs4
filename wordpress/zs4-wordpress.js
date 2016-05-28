zs4.wordpress = {
	ajax:function(){
		$.post(
			ajaxurl, 
			{
				'action': 'zs4',
				'data':   'foobarid'
			}, 
			function(response){
				alert('The server responded: ' + response);
			}
		);	
	}
	
};
