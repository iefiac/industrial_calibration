/*
 * Software License Agreement (Apache License)
 *
 * Copyright (c) 2013, Southwest Research Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BASIC_TYPES_H_
#define BASIC_TYPES_H_

#include <boost/shared_ptr>
#include <industrial_extrinsic_cal/ceres_excal.hpp> // needed for Point3d

namespace industrial_extrinsic_cal {

  /*! \brief A region of interest in an image */
  typedef struct{
    int x_min;
    int x_max;
    int y_min;
    int y_max;
  } Roi;

  /*! Brief Point3d defines a ceres_structure for a point in 3D space */
  typedef struct { 
    union{
      struct{ 
	double x;		/**< position x */ 
	double y;		/**< position y */ 
	double z;		/**< position z */ 
      };
      double pb[3];		/**< a parameter block with all three elements
    };
  }Point3d;
  
  /*! Brief Pose6d defines a ceres_structure for a pose in 3D space 
   *   x,y,z have their natrual meanging
   *   ax,ay,az define the rotation part of the pose using angle axis notation
   */
  typedef struct { 
    union{
      struct{
	double x;		/**< position x */ 
	double y;		/**< position y */ 
	double z;		/**< position z */ 
	double ax;		/**< angle axis x value */ 
	double ay;		/**< angle axis y value */ 
	double az;		/**< angle axis z value */ 
      };
      struct{		
	double pb_loc[3];	/**< parameter block for position */
	double pb_aa[3];	/**< parameter block for rotation */
      };
      struct{
	double pb_pose[6];	/**< a third option with a single block for 6dof pose */
      };
    };
  }Pose6d;
				    
  /*! \brief A target's information */
  typedef struct{
    std::string target_name;
    std::target_type;
    bool is_moving;  /** observed in multiple locations or it fixed to ref frame */
    Pose6d pose;
    std::vector<Point3d> pts; /** an array of points expressed relative to Pose p. */
  } Target;

  /*! \brief An observation is the x,y image location of a target's point in an image*/
  typedef struct { 
    boost::shared_ptr<Target> target; /**< pointer to target who's point is observed */
    int point_id;			/**< point's id in target's point array */
    double image_loc_x;			/**< target point was found at image location x */
    double image_loc_y;			/**< target point image location y */
  }Observation;

  /*! \brief A vector of observations made by a single camera of posibly multiple targets */
  typedef struct { 
    std::vector<Observation> observation;
  }CameraObservations;

/*! Brief CameraParameters defines both the intrinsic and extrinsic parameters of a camera
 */
typedef struct{ 
  union{
    struct{ 
      double aa[3];		      /** angle axis data */
      double pos[3];		      /** position data */
      double fx;		      /** focal length in x */
      double fy;		      /** focal length in y */
      double cx;                      /** central pixel x value */
      double cy;                      /** central pixel y value */
      double k1;                      /** 2nd order radial distortion parameter */
      double k2;                      /** 4th order radial distortion parameter */
      double k3;                      /** 6th order radial distortion parameter */
      double p1;                      /** 1st tangential distortion parameter */
      double p2;                      /** 2nd tangential distortion parameter */
    };
    struct{ /** parameter blocks for ceres */
      double pb_extrinsics[6];	      /** parameter block for intrinsics */
      double pb_intrinsics[9];        /** parameter block for extrinsics */
    };
    struct{
      double pb_all[15];         /** parameter block for both */
    };
  };
}CameraParameters;


}
#endif