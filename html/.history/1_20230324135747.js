<script type="text/javascript">
   function check(f){
     var str = f.username,value;
     var c = new Array('script','>','<','input','img');
     for(var i=0; i<c.length; i++){
        if(str.indexOf(c[i])!=-1){
            alert('你输入的数据存在敏感字符 :'+ c[i]);
            return false  ;
        }
     }
     return turn  ;
   }
   </script>