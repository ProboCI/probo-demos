/**
 * Project: jQuery Lightbox
 * Description: A super lightweight lightbox plugin
 * Author: Peter Bleickardt
 * Version: 2.3.1
 */
;(function ($, window, document, undefined) {

  var pluginName = "lightbox",
    dataPlugin = "plugin_" + pluginName,
    defaults = {
      "class" : "",
      "title" : "",

      // Callbacks
      "onOpen": null,
      "onClose": null
    }
  ;

  /**
   * Initilization steps on document load
   */
  $(document).ready(function(){
    var $html = $("html");

    // Handle scrollbar width for overlay display

    // Get current width
    currentWidth = $(window).width();

    // Get locked width
    $html.addClass("lightbox-test");
    lockedWidth = $(window).width();
    $html.removeClass("lightbox-test");

    // Get difference
    var difference = lockedWidth - currentWidth;

    // Append style to <head>
    if (difference) {
      $("<style type=\"text/css\">.with-lightbox { margin-right: " + difference + "px; }</style>")
        .appendTo($("head"))
      ;
    }
  });

  /**
   * Construct dialog
   * @param  {DOMElement} element
   * @param  {Object}     options
   * @return {Object}             Holds the overlay and lightbox
   */
  var constructDialog = function (element, options) {

    var $content = $('<div class="lightbox-content">')
      .append(element.show())
    ;
    var $title = $('<div class="lightbox-title">')
      .html(options.title)
    ;
    var $lightbox = $('<div class="lightbox-layout">').append(
        $('<div class="lightbox">')
        .append($title)
        .append($('<div class="lightbox-close">'))
        .append($content)
      )
    ;
    var $overlay = $('<div class="lightbox-overlay" style="display: none;">')
      .addClass(options['class'])
      .append($lightbox)
    ;

    $("body").append($overlay);

    return {
      "overlay": $overlay,
      "lightbox": $lightbox,
      "content": $content,
    }
  }


  /**
   * Plugin constructor
   * @param  {DOMElement} element
   */
  var Plugin = function (element) {
    this.options = $.extend( {}, defaults );
  };

  Plugin.prototype = {

    init: function (options) {

      // Extend options
      $.extend( this.options, options );

      // Init
      var _this = this,
        content = this.element
      ;

      // Construct
      var parts = constructDialog(content, this.options);
      this.$overlay = parts['overlay'];
      this.$lightbox = parts['lightbox'];
      this.$content = parts['content'];

      // Handle close
      var $close = this.$lightbox.find(".lightbox-close");
      this.$overlay.add($close)
        .on("click tap touchstart", function(event){
          $target = $(event.target);
          console.log('click close', $target[0] == _this.$overlay[0], $close.has($target).length, $target.is($close));
          if (
            $target.is($close) // close button
            || !_this.$lightbox.has($target).length // outside lightbox
          ) {
            _this.hide();
          }
          event.stopPropagation();
        })
      ;

      return this;

    },

    destroy: function () {
      // unset Plugin data instance
      this.element.data( dataPlugin, null );
    },

    show: function() {

      // Init
      this.$lightbox.show();
      this.$overlay.fadeIn(200);

      // Add <html> class
      $("html").addClass("with-lightbox");

      // Bind
      var _this = this;
      $(document).bind("keyup.lightbox", function(e) {
        switch (e.keyCode) {
          case 27: // escape
            _this.hide();
          break;
        }
      });

      // Fire callback
      if (typeof this.options.onOpen == "function") {
        this.options.onOpen();
      }

      // Fire event
      this.element.trigger("show.lightbox");

    },

    hide: function() {
      var _this = this;
      this.$overlay.fadeOut(100, function(){
        // Remove <html> class
        $("html").removeClass("with-lightbox");

        // Unbind
        $(document).unbind(".lightbox");

        // Fire callback
        if (typeof _this.options.onClose == "function") {
          _this.options.onClose();
        }

        // Fire event
        _this.element.trigger("hide.lightbox");

      });
    }

  }

  /**
   * Plugin wrapper
   */
  $.fn[pluginName] = function(arg) {

    var args, instance;

    // Only allow the plugin to be instantiated once
    if (!(this.data(dataPlugin) instanceof Plugin)) {
      this.data(dataPlugin, new Plugin(this));
    }

    instance = this.data(dataPlugin);
    if (!instance) return;

    instance.element = this;

    if (typeof arg === 'undefined' || typeof arg === 'object') {
      if (typeof instance['init'] === 'function') {
        return instance.init(arg);
      }
    } else if (typeof arg === 'string' && typeof instance[arg] === 'function') {
      args = Array.prototype.slice.call(arguments, 1);
      return instance[arg].apply(instance, args);
    } else {
      $.error('Method ' + arg + ' does not exist on jQuery.' + pluginName);
    }
  };

}(jQuery, window, document));
