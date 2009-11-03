// Persistence of Vision Ray Tracer Scene Description File
// File: crowd_example.pov
// Vers: 3.6
// Desc: Sample scene to show usage of the rf_crowd_pub macro
// Date: Oct 26, 2008 
// Auth: Rob Fitzel
// Units: - 
// 
// scene constants and overrides ////////////////////////////////////////////// 
 
// includes ///////////////////////////////////////////////////////////////////

// Scene Controls /////////////////////////////////////////////////////////////

#declare example = 5;  // set to 0-3
                 //0 = distant crowd facing camera
                 //1 = crossing the street
                 //2 = waiting in line
                 //3 = army of suits
                 //4 = dance floor
                 //5 = large crowd


// camera
#declare view = 2; 

// lights
#declare cam_light = 1;
#declare sun_light = 2;
#declare SunPos    = <-100,100,-100>;

// randomizers 

// special effects
#declare rad = 0;

global_settings { 
  max_trace_level 20 
  #if (rad>0) 
    #include "rad_def.inc"
    radiosity {
      #if (rad =1) Rad_Settings(Radiosity_IndoorLQ, off, off)  #end
      #if (rad =2) Rad_Settings(Radiosity_IndoorHQ, off, off)  #end
      
      // overrides 
    }
  #end
}

// conditional includes ///////////////////////////////////////////////////////

                                                     
// Camera /////////////////////////////////////////////////////////////////////

#switch (view)
  #case (0)  // top view
    #declare CamPos    = <10, 100, 0> ;
    #declare CamLookAt = <10,0,0>;
    #break
  #case (1) //  
    #declare CamPos    = <0, 4, -15>;
    #declare CamLookAt = <0,4,0>;
    #break 
  #case (2) //  
    #declare CamPos    = <10, 20, -15>;
    #declare CamLookAt = <8,15,0>;
    #break 
  #else  
    #declare CamPos    = <0, 5, -50>; 
    #declare CamLookAt = <0,5,0>; 

#end


camera {
  location  CamPos 
  look_at   CamLookAt

} 


// Lights /////////////////////////////////////////////////////////////////////

#if (cam_light>0) 
  light_source {0*x rgb cam_light translate CamPos}
#end 
  
#if (sun_light>0)
  light_source {0*x rgb sun_light translate SunPos}
#end


background {rgb <0.282,0.522,0.796>}  


// Textures ///////////////////////////////////////////////////////////////////


// Scene  Objects ///////////////////////////////////////////////////////////// 

plane {y, 0 pigment {rgb 0.5}}

#include "rf_crowd_pub.inc"  


#local psd = seed(4142);  
#local i=0;  


#switch (example)
  #case(0) /////////////////////////////////////////////////////////////////////
    #while (i<100)
      billboard_person(i,                   // character
                       pose_rand,           // walking and standing
                       dir_facing,          // facing the camera
                       RRand(5.5,6,psd),    // random heights
                       no_lighting,         //  flat lighting
                       psd,                 // random seed
                       CamPos,              // camera position (so billboards properly rotated)
                       <RRand(-50,50,psd),0,RRand(0,150,psd)> // billboard position
                       )
      #local i=i+1;
    #end
    #break
  #case(1) /////////////////////////////////////////////////////////////////////
    #while (i<100)  
      billboard_person(rand_char,                   // character
                       pose_walk,           // walking 
                       dir_cross,           // walking left and right
                       RRand(5.5,6,psd),    // random heights
                       no_lighting,         // flat lighting
                       psd,                 // random seed
                       CamPos,              // camera position (so billboards properly rotated)
                       <RRand(-50,50,psd),0,RRand(30,40,psd)> // billboard position
                       )
    
    
      #local i=i+1;
    #end
    #break  
  #case(2) /////////////////////////////////////////////////////////////////////
    #while (i<100)  
      billboard_person(i,                   // character
                       pose_stand,          // standing in line 
                       7,                   // facing forward left (7*45 = 315 degree rotation)
                       RRand(5.5,6,psd),    // random heights
                       left_lighting,       // light from left (consistent with shadows)
                       psd,                 // random seed
                       CamPos,              // camera position (so billboards properly rotated) 
                       <-i*2,0,i*2>         // billboard position
                       )
    
    
      #local i=i+1;
    #end
    #break
  #case(3) /////////////////////////////////////////////////////////////////////
    #while (i<2000)  
      billboard_person(3,                  // formal suit guy
                       pose_rand,          // walking 
                       dir_facing,         // walking left and right
                       RRand(2,2.2,psd),   // random heights
                       left_lighting,      // light from the left
                       psd,                // random seed
                       CamPos,             // camera position (so billboards properly rotated) 
                       <RRand(-50,50,psd),0,RRand(0,150,psd)> // billboard position
                       )
    
    
      #local i=i+1;
    #end 
  #case(4) /////////////////////////////////////////////////////////////////////
    #while (i<20)  
      billboard_person(1,         // women
                       pose_stand,          // walking 
                       6,                  // walking left and right
                       RRand(5,5.5,psd),   // random heights
                       left_lighting,      // light from the left
                       psd,                // random seed
                       CamPos,             // camera position (so billboards properly rotated) 
                       <RRand(-2,-20,psd),0,RRand(0,50,psd)> // billboard position
                       )
      billboard_person(2,         // women
                       pose_stand,          // walking 
                       6,                  // walking left and right
                       RRand(5,5.5,psd),   // random heights
                       left_lighting,      // light from the left
                       psd,                // random seed
                       CamPos,             // camera position (so billboards properly rotated) 
                       <RRand(-2,-20,psd),0,RRand(0,50,psd)> // billboard position
                       )
      billboard_person(0,         // men
                       pose_stand,          // walking 
                       2,                  // walking left and right
                       RRand(5,5.5,psd),   // random heights
                       left_lighting,      // light from the left
                       psd,                // random seed
                       CamPos,             // camera position (so billboards properly rotated) 
                       <RRand(20,2,psd),0,RRand(0,50,psd)> // billboard position
                       )
      billboard_person(3,         // men
                       pose_stand,          // walking 
                       2,                  // walking left and right
                       RRand(5,5.5,psd),   // random heights
                       left_lighting,      // light from the left
                       psd,                // random seed
                       CamPos,             // camera position (so billboards properly rotated) 
                       <RRand(20,2,psd),0,RRand(0,50,psd)> // billboard position
                       )
      #local i=i+1;
    #end
    #break
    
  #else  /////////////////////////////////////////////////////////////////////
    #while (i<5000)  
      billboard_person(i,                  // character
                       pose_rand,          // walking 
                       dir_rand,           // walking left and right
                       RRand(2,2.2,psd),   // random heights
                       left_lighting,      // light from the left
                       psd,                // random seed
                       CamPos,             // camera position (so billboards properly rotated) 
                       <RRand(-50,50,psd),0,RRand(0,150,psd)> // billboard position
                       )
    
    
      #local i=i+1;
    #end
  #end  
// Notes ///////////////////////////////////////////////////////////////////////
/*




*/





   
