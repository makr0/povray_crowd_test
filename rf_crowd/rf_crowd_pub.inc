// Persistence of Vision Ray Tracer Include File
// File: rf_crowd_pub.inc
// Vers: 3.6
// Desc: crowd macro
// Date: Oct 26, 2008
// Auth: Rob Fitzel

/* 
 billboard_person macro usage
 parameters:
 char - character to draw (use rand_char to select a random character)
 pose - pose_walk or pose_stand 
 dir  - (0-7) which direction person is facing (45degree increments 0=face-on 1= 45 degree right, etc)
      - dir_rand (people face random direction)
      - dir_cross (people crossing infront of camera - no front or back view)
      - dir_across (people crossing infront of camera - only profile views)
      - dir_direct (people facing camera or directly away from camera - front and back views only)
      - dir_facing (people directly facing camera or slightly left and right)
       
 sc    - scale (original billboard size is 1 unit x 1 unit)
       - make a random value within a small range (e.g., 5.5-6) to add a little variety
 light - no_lighting = flat lighting
       - left_lighting = lit from the left
       - right_lighting = lit from the right side
 psd   - random seed
 cam_pos - camera position
 pers_position - position of billboard
          
*/

#include "rand.inc" 
#include "math.inc"



// new method to same memory
#declare reuse_billboards = 1; 

// parameter constants
#declare rand_char   = -1; 
#declare pose_stand  = 0;
#declare pose_walk   = 1;
#declare pose_rand   = 2;

// directional control
#declare dir_max    =  7;
#declare dir_rand   = -1; // facing random direction
#declare dir_cross  = -2; // people crossing infront of camera (no front or back view) 
#declare dir_across = -3; // people crossing infront of camera (only left and right views)
#declare dir_direct = -4; // directly facing or facing away
#declare dir_facing = -5; // directly facing camera or slightly left and right 

// lighting
#declare no_lighting = 0;
#declare left_lighting = 1;
#declare right_lighting = 2;

// reuse array dimensions
#declare num_poses = 2; // stand, walk 
#declare num_dirs  = 8;    
#declare num_lights = 2; // 0 and 1


/* character list
standing people
0  casual man looking at watch
1  semi-formal woman waiting
2  bookish woman
3  formal man with suit

walker's club
0  semi-formal woman in white
1  casual woman
2  semi-formal man
3  formal man in suit

*/
// if you add new billboards, increment the constant(s) below
#declare max_stand_idx = 4;
#declare max_walk_idx  = 4;
  
 
  
// initialize arrays of used billboards
// these arrays reduce memory consumption by reusing already allocated billboards rather than allocating a new instance 
#macro init_rand_billboard_person()

  #declare num_chars = max(max_stand_idx,max_walk_idx)+1;
  
  #declare billboard_used = array[num_poses][num_chars][num_dirs][num_lights];
  #declare billboard_objs = array[num_poses][num_chars][num_dirs][num_lights]; 
  // keep track of billboards used  
  #local i=0;
  #while (i<num_poses)
    #local j=0;
    #while (j<num_chars)
      #local k=0;
      #while (k<num_dirs) 
        #local l=0;
        #while (l<num_lights)
          #declare billboard_used[i][j][k][l] = 0;
          #local l=l+1;
        #end
        #local k=k+1;
      #end
      #local j=j+1;
    #end
    #local i=i+1;
  #end
#end


// init the arrays
init_rand_billboard_person()


// billboard image gets projected onto this shape
// using plane avoids artifacts seen when using boxes
#declare billboard_shape =    
 difference {     
     plane {z,0 }
     plane {y,1 inverse pigment {rgbt 1}} 
     plane {x,0  pigment {rgbt 1}} 
     plane {x,1  inverse pigment {rgbt 1}} 
     plane {y,-0.1 pigment {rgbt 1}}  
     bounded_by {box {<0,0,-0.00001>,<1,1,0.00001> }} // BIG speed improvement!!!
   };


/* 
 billboard_person macro
 parameters:
 char - character to draw (use rand_char to select a random character)
 pose - pose_walk or pose_stand 
 dir  - (0-7) which direction person is facing (45degree increments 0=face-on 1= 45 degree right, etc)
      - dir_rand (people face random direction)
      - dir_cross (people crossing infront of camera - no front or back view)
      - dir_across (people crossing infront of camera - only profile views)
      - dir_direct (people facing camera or directly away from camera - front and back views only)
      - dir_facing (people directly facing camera or slightly left and right)
       
 sc    - scale (original billboard size is 1 unit x 1 unit)
       - make a random value within a small range (e.g., 5.5-6) to add a little variety
 light - no_lighting = flat lighting
       - left_lighting = lit from the left
       - right_lighting = lit from the right side
 psd   - random seed
 cam_pos - camera position
 pers_position - position of billboard
          
*/  

#macro billboard_person(char, pose,dir,sc,light_dir, psd,cam_pos,pers_pos)

  // get direction character is facing (which angle to employ)
  #local img_dir = dir;
  
  #if (dir > dir_max)
    #local dir = dir_rand;
  #end
     
  #if (dir = dir_rand)
    #local img_dir = int(rand(psd)*8); 
  #end 
  
  #if (dir = dir_cross) // people crossing infront of camera (no front or back view)
    #local img_dir = int(rand(psd)*8);
    #if (img_dir = 0)
      #local img_dir = 1;
    #end
    #if (img_dir = 4)
      #local img_dir = 5;
    #end
  #end 
  
  #if (dir = dir_across) //people crossing infront of camera (only left and right views)
    #if (rand(psd)<0.5)
      #local img_dir = 2;
    #else
      #local img_dir = 6;
    #end  
  #end    
  
  #if (dir = dir_facing)
    #switch (rand(psd))
      #range(0,0.333)     #local img_dir = 7; #break
      #range(0.333,0.667) #local img_dir = 0; #break
      #else               #local img_dir = 1; #break
    #end
  #end
  

  #if (dir = dir_direct) //people facing towards (dir 0) and away (dir 4) from camera
    #if (rand(psd)<0.5)
      #local img_dir = 0;
    #else
      #local img_dir = 4;
    #end  
  #end    
    

  // get pose (walk or stand)
  #local curr_pose = pose; 
  #if (curr_pose = pose_rand)
    #if (rand(psd) <0.5)
      #local curr_pose = pose_walk;
    #else
      #local curr_pose = pose_stand;
    #end
  #end  

  
  // build the image filename in stages
  #if (curr_pose = pose_walk)
    #local img = "walk"; 
    #local max_char_idx = max_walk_idx;
  #end
  #if (curr_pose = pose_stand)
    #local img = "stand"; 
    #local max_char_idx = max_stand_idx;
   // until billboards with standing poses support lighting, ignore light_dir
   // #local light_dir = no_lighting;
  #end 
  
    
  // pick a character
  #local char_idx = int(char);

   
  #if (char_idx = rand_char)
    #local char_idx  = int(rand(psd)*max_char_idx); // which character
  #end
  
  #if (char_idx >= max_char_idx) 
    #local char_idx = mod(char_idx,max_char_idx); 
  #end
                  

  // append character index to filename
  #local img_base = concat(img,str(char_idx,0,0));  

  // append direction to filename 
  #switch(light_dir)
    #case (no_lighting)
      #local img = concat(img_base,"-",str(img_dir,0,0),".png");
      #local img2= concat(img_base,"-",str(mod((img_dir+2),7),0,0),".png"); 
      #local lit = 0;  
     
     // since lighting is flat, we sometimes invert the image to add more randomness
     #local rev = 1; 
      #if (dir = dir_rand)
        #if (rand(psd) <0.5)
          #local rev = -1;  
        #end
      #end 
      
      #break 
    #case(left_lighting)
      #local img = concat(img_base,"lit-",str(img_dir,0,0),".png");
      #local img2= concat(img_base,"lit-",str(mod((img_dir+2),7),0,0),".png");
      #local rev = -1; // invert the image so lights come from left side
      #local lit = 1;
      #break
    #case(right_lighting)
      #local img = concat(img_base,"lit-",str(img_dir,0,0),".png");
      #local img2= concat(img_base,"lit-",str(mod((img_dir+2),7),0,0),".png");
      #local rev = 1;
      #local lit = 1;
      #break
    #else
      Error in lights parameter!
  #end
      


  // if we've used this combination before, retrieve the object from last time (saves memory) 
  #if (reuse_billboards)   
    #if (billboard_used[curr_pose][char_idx][img_dir][lit] = 0)
      #declare  billboard_used[curr_pose][char_idx][img_dir][lit] = 1; 
      #declare  billboard_objs[curr_pose][char_idx][img_dir][lit] =  
         object {billboard_shape texture {pigment{image_map{png img interpolate 2 once}} finish {phong 0}} translate <-0.5,0,0> scale sc  }
          
    #end
  #end 

       
  #debug img
  #debug "\n"

  #local img_rot  = atan2d( (pers_pos.x-cam_pos.x),(pers_pos.z-cam_pos.z) ); // keep img oriented to camera 
  #local img_rot2 = img_rot+90;
    
    
  #if (reuse_billboards)   
      object {billboard_objs[curr_pose][char_idx][img_dir][lit] scale <rev,1,1> rotate y*img_rot translate pers_pos}
  #else
    box {<0,0,0>,<1,1,0.00001> 
       texture {pigment{image_map{png img}} finish {phong 0}}  
       translate <-0.5,0,0> 
       scale sc 
       rotate y*img_rot 
       translate pers_pos
    } 
  #end

        
        
        
#end 


