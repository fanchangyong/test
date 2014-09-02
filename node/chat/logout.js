
function logout(){
	var xhr=new XMLHttpRequest();
	xhr.onreadystatechange = function(){
		if(xhr.readyState == 4 && xhr.status == 200){
			var obj = JSON.parse(xhr.responseText);
			if(obj.result=='ok'){
				document.getElementById('logoutresult').innerText=
					'Logout Success,will take you home after 1 second!';
				setTimeout(function(){
					window.location='/';
				},1000);
			}else{
				document.getElementById('logoutresult').innerText=
					'logout failed!';
			}
		}
	}
	xhr.open('POST','/logout');
	xhr.send();
}
