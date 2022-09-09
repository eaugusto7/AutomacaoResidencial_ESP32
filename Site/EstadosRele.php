<?php
    include('conexao.php');
    
    $sql = "SELECT * FROM Reles";
    
    $stmt = $PDO->prepare($sql);
    $stmt->execute();
    
    $result = $stmt->fetchAll();
    
    foreach($result as $value){
        echo $value['estado'];
    }
?>