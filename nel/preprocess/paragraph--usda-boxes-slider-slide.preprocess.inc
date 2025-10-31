<?php

/**
 * Implements hook_preprocess_paragraph__usda_boxes_slider_slide().
 */
function nel_preprocess_paragraph__usda_boxes_slider_slide(&$variables) {
  $panel = $variables['paragraph'];

  // Add the panel class
  $variables['attributes']['class'][] = 'usda-boxes-slider-slide';

}
