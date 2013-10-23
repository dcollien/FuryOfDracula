(function testExpandConnections( ) {
   // Tests
   assert(
     list.isEqual(
       expandConnections( 1, gameMap.railConnections, 'SO' ),
       [ 'BE', 'SA', 'VR' ]
     ),
     'expandConnections'
   );
   
   assert(
     list.isEqual(
       expandConnections( 2, gameMap.railConnections, 'SO' ),
       [ 'SO', 'SZ', 'BE', 'SA', 'VR' ]
     ),
   'expandConnections'
   );
   
   assert(
     list.isEqual(
       expandConnections( 3, gameMap.railConnections, 'SO' ),
       [ 'BE', 'SA', 'VR', 'BC', 'BD', 'SO', 'SZ' ]
     ),
     'expandConnections'
   );
   
   assert(
     list.isEqual(
       expandConnections( 4, gameMap.railConnections, 'SO' ),
       [ 'SO', 'SZ', 'BE', 'SA', 'VR', 'CN', 'GA', 'VI', 'BC', 'BD' ]
     ),
     'expandConnections'
   );   
})( );