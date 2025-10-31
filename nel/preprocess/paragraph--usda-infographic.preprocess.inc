<?php

/**
 * Implements hook_preprocess_paragraph__usda_infographic().
 */
function nel_preprocess_paragraph__usda_infographic(&$variables) {
  // $paragraph = $variables['paragraph'];

  // Add the class
  $variables['attributes']['class'][] = 'usda-infographic';

  // Mark the first accordion as expanded
  $variables['content']['field_paragraphs'][0]['#usda_expand'] = TRUE;
}
