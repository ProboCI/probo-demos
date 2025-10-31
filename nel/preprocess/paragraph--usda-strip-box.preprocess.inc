<?php

/**
 * Implements hook_preprocess_paragraph__usda_strip_box().
 */
function nel_preprocess_paragraph__usda_strip_box(&$variables) {
  $media = $variables['paragraph'];

  // Add the class
  $variables['attributes']['class'][] = 'usda-strip-box';

}
