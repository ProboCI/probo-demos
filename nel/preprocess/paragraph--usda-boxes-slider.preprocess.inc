<?php

/**
 * Implements hook_preprocess_paragraph__usda_boxes_slider().
 */
function nel_preprocess_paragraph__usda_boxes_slider(&$variables) {
  // $panel = $variables['paragraph'];

  // Add the panel class
  $variables['attributes']['class'][] = 'usda-boxes-slider';

}
