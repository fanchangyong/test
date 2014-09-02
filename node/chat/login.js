
document.getElementById('btnLogin').onclick = function(){
	var xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function(){
		if(xhr.readyState == 4){
			if(xhr.status == 200){
				var ret = JSON.parse(xhr.responseText);
				if(ret.result=='ok'){
					document.getElementById('loginresult').innerText=
						'Login OK,I will take you home after 1 second!';
					setTimeout(function(){
						window.location="/";
					},1000);
				}else{
					document.getElementById('loginresult').innerText=ret.value;
				}
			}
		}
	}
	xhr.open('POST','/login');
	xhr.setRequestHeader('Content-type','application/json');
	var username = document.getElementById('username').value;
	var password = document.getElementById('password').value;
	var str = JSON.stringify({'username':username,'password':password}); 
	xhr.send(str);
}
