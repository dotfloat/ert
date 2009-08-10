#ifndef __PLOT_DRIVER_H__
#define __PLOT_DRIVER_H__

#include <plot_const.h>
#include <plot_range.h>
#include <double_vector.h>


typedef struct plot_dataset_struct plot_dataset_type;
typedef struct line_attribute_struct  line_attribute_type;
typedef struct point_attribute_struct point_attribute_type;
typedef struct plot_driver_struct     plot_driver_type;

typedef void (set_labels_ftype)       (plot_driver_type * driver , const char *title , const char * xlabel , const char * ylabel, plot_color_type label_color , double label_font_size);
typedef void (window_size_ftype)      (plot_driver_type * driver , int width , int heigth);
typedef void (close_driver_ftype)     (plot_driver_type * driver );
typedef void (set_axis_ftype)         (plot_driver_type * driver , plot_range_type * range , const char * timefmt , plot_color_type box_color , double tick_font_size);

typedef void (plot_xy_ftype)          (plot_driver_type * driver , const char * label , const double_vector_type * x , const double_vector_type * y , plot_style_type style , line_attribute_type line_attr , point_attribute_type point_attr);
typedef void (plot_xy1y2_ftype)       (plot_driver_type * driver , const char * label , const double_vector_type * x , const double_vector_type * y1 , const double_vector_type * y2 , line_attribute_type line_attr );
typedef void (plot_x1x2y_ftype)       (plot_driver_type * driver , const char * label , const double_vector_type * x1 , const double_vector_type * x2 , const double_vector_type * y , line_attribute_type line_attr );
typedef void (plot_hist_ftype)        (plot_driver_type * driver , const char * label , const double_vector_type * x , line_attribute_type line_attr);

    

struct plot_driver_struct {
  char                    * driver_name;
  void               	  * state;	       
  
  close_driver_ftype      * close_driver;    

  set_labels_ftype    	  * set_labels;
  window_size_ftype       * set_window_size;
  set_axis_ftype          * set_axis;
  
  plot_xy_ftype           * plot_xy;
  plot_xy1y2_ftype        * plot_xy1y2;
  plot_x1x2y_ftype        * plot_x1x2y;
  plot_hist_ftype         * plot_hist;
};



struct line_attribute_struct {
  plot_color_type      line_color;   /**< The color for the line part of the plot. */
  plot_line_style_type line_style;   /**< The style for lines. */
  double               line_width;   /**< Scale factor for line width  : starts with PLOT_DEFAULT_LINE_WIDTH */
};




struct point_attribute_struct {
  plot_color_type      point_color;  /**< The color for the points in the plot. */
  plot_symbol_type     symbol_type;  /**< The type of symbol. */
  double               symbol_size;  /**< Scale factor for symbol size : starts with PLOT_DEFAULT_SYMBOL_SIZE */
};




void               plot_driver_free( plot_driver_type * driver );
plot_driver_type * plot_driver_alloc_empty(const char * driver_name);

void plot_driver_plot_xy( plot_driver_type * driver , const char * label , 
                          const double_vector_type * x  , 
                          const double_vector_type * y  , 
                          plot_style_type style         , 
                          line_attribute_type line_attr , 
                          point_attribute_type point_attr);

void plot_driver_plot_xy1y2(plot_driver_type * driver     , 
                            const char * label , 
                            const double_vector_type * x  , 
                            const double_vector_type * y1  , 
                            const double_vector_type * y2  , 
                            line_attribute_type line_attr);

void plot_driver_plot_x1x2y(plot_driver_type * driver      , 
                            const char * label             , 
                            const double_vector_type * x1  , 
                            const double_vector_type * x2  , 
                            const double_vector_type * y   , 
                            line_attribute_type line_attr);

void plot_driver_plot_yline( plot_driver_type * driver , const char * label , double xmin , double xmax , double y0 , line_attribute_type line_attr);

void plot_driver_plot_xline( plot_driver_type * driver , const char * label , double x0 , double ymin , double ymax , line_attribute_type line_attr);

void plot_driver_plot_hist( plot_driver_type * driver, const char * label , const double_vector_type * x , line_attribute_type line_attr);

void plot_driver_set_axis( plot_driver_type * driver , plot_range_type * range , const char * timefmt , plot_color_type box_color , double tick_font_size);

void plot_driver_set_labels(plot_driver_type * driver , const char *title , const char * xlabel , const char * ylabel, plot_color_type label_color , double label_font_size);

void plot_driver_set_window_size(plot_driver_type * driver , int width , int height);

void plot_driver_assert( const plot_driver_type * driver );

#endif
