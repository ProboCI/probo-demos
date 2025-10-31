<?php

/**
 * Implements hook_preprocess_paragraph__usda_picture_text_row().
 */
function nel_preprocess_paragraph__usda_picture_text_row(&$variables) {
  $row = $variables['paragraph'];

  // Add the panel class
  $variables['attributes']['class'][] = 'usda-pictext';

  // Add the selected picture size class
  $pictureSizeClass = null;
  $pictureSize = $row->field_usda_picture_size->value;
  if ($pictureSize) {
    switch ($pictureSize) {
      case 'small':
        $pictureSizeClass = 'usda-pictext-sm';
      break;
      case 'medium':
        $pictureSizeClass = 'usda-pictext-md';
      break;
      case 'large':
        $pictureSizeClass = 'usda-pictext-lg';
      break;
      case 'full':
        $pictureSizeClass = 'usda-pictext-full';
      break;
      case 'original':
      default:
        // no class
      break;
    }
  }
  if ($pictureSizeClass) {
    $variables['attributes']['class'][] = $pictureSizeClass;
  }
}
