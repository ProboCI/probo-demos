<?php

/**
 * Implements hook_preprocess_paragraph__usda_container().
 */
function nel_preprocess_paragraph__usda_container(&$variables) {
  $container = $variables['paragraph'];

  // Add the container class
  $variables['attributes']['class'][] = 'usda-container';

  // Add the user input class
  $classes = $container->field_usda_css_classes->value;
  if ($classes) {
    $variables['attributes']['class'][] = $classes;
  }

}
