<?php

/**
 * Implements hook_preprocess_paragraph__usda_strip().
 */
function nel_preprocess_paragraph__usda_strip(&$variables) {
  $media = $variables['paragraph'];

  // Add the class
  $variables['attributes']['class'][] = 'usda-strip';

}
