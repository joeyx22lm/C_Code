<?php
//
//  Primitive Root
//
//  Created by Joseph Orlando on 3/13/15.
//  Copyright (c) 2015 Joseph Orlando. All rights reserved.
//

function PrimitiveRoot($a, $p){
  $Seen = array();
  for($i = 1;$i<$p;$i++){
      $Pr = (pow($a, $i) % $p);
      // is within numeric bounds && unique?
      if($Pr < 1 || $Pr > ($p-1) || isset($Seen[$Pr])){
          // nahh
          return false;         
      }
      $Seen[$Pr] = true;  
  }
  // yessir
  return true;
}
echo 'is 2 pR of 13? = ';
if(PrimitiveRoot(3, 11)){
  echo 'yes!'; 
}else{
  echo 'no!'; 
}
?>
