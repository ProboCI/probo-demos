<?php

/**
 * Implements hook_preprocess_paragraph__usda_slider().
 */
function nel_preprocess_paragraph__usda_slider(&$variables) {
  $slider = $variables['paragraph'];

  // Add the slider class
  $variables['attributes']['class'][] = 'usda-slider';

  // Add the selected color class
  $color = $slider->field_background_color->value;
  if ($color) {
    $variables['attributes']['class'][] = $color;
  }

}
