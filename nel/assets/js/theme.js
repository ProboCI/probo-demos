/**
 *
 * Dietary Guidelines
 *
 */
(function($){

  //
  // Primary menu
  //
  $(function(){
    $('.usa-nav-primary.usa-accordion').each(function(){
        var $nav = $(this),
            $buttons = $nav.find('.usa-accordion-button'),
            $menus = $nav.find('.usa-nav-submenu'),
            $containers = $buttons.closest('li')
        ;
        $(document).on('click', function(event){
            var $target = $(event.target);
            if (!$containers.has($target).length) {
                // Force the menus closed
                $buttons.attr('aria-expanded', false);
                $menus.attr('aria-hidden', true);
            }
        });
    });
  });

  //
  // Media lightbox
  //
  $(function(){
    $('.usda-media-zoom').each(function(){
      var $media = $(this),
        $trigger = $media.find('.usda-media-zoom-button'),
        $picture = $media.find('.media--type-image img').first().clone(),
        caption = $media.data('caption')
      ;
      if (caption) caption = $('<div>').html(caption).text();
      $trigger.on('click', function(){
        $lightbox = $('<div>')
          .append(
            $('<div>')
              .addClass('picture')
              .append($picture)
          )
          .append(
            $('<div>')
              .addClass('caption')
              .html(caption)
          )
        ;
        $lightbox.lightbox().show();
      });
    });
  });

  //
  // Tabs
  //
  $(function(){
    $('.usda-tabs').each(function(){
      var $tabs = $(this),
        $buttons = $tabs.find('.usda-tab-button'),
        // $contents = $()
        $contents = $tabs.find('.usda-tab-content')
      ;

      // Roll through buttons to set initial state and wire up the click event
      $buttons.each(function(){
        var $button = $(this);
        $button.on('click', function(){
          var $button = $(this);
          toggleTab($button);
        });
      });

      // Handle incoming tab request in hash
      var hash = window.location.hash.substring(1);
      if (hash) {
        var $button = $buttons.filter('[aria-controls="' + hash + '"]');
        if ($button.length) {
          toggleTab($button);
        }
      }

      // Function to toggle a tab
      function toggleTab($button) {
        var controls = $button.attr('aria-controls'),
          $content = $('#' + controls)
        ;
        $contents.attr('aria-hidden', true);
        $content.attr('aria-hidden', false);
        $buttons.attr('aria-expanded', false);
        $button.attr('aria-expanded', true);
      }
    });

  });

  //
  // Slider
  //
  $(function(){
    $('.usda-slider').each(function(){
      var $slider = $(this),
        $slides = $slider.find('.slides').first(),
        $arrowHost = $slider.find('.arrow-host').first()
      ;

      $slides.slick({
        infinite: false,
        slidesToShow: 1,
        // centerMode: true,
        // centerPadding: '0',
        // variableWidth: true,
        appendArrows: $arrowHost
      });

    });
  });

  //
  // Boxes Slider
  //
  $(function(){
    $('.usda-boxes-slider').each(function(){
      var $slider = $(this),
        $slides = $slider.find('.slides').first(),
        $arrowHost = $slider.find('.arrow-host').first()
      ;

      $slides.slick({
        infinite: false,
        slidesToShow: 4,
        slidesToScroll: 4,
        appendArrows: $arrowHost,
        responsive: [
          {
            breakpoint: 951,
            settings: {
              slidesToShow: 3,
              slidesToScroll: 3
            }
          },
          {
            breakpoint: 600,
            settings: {
              slidesToShow: 2,
              slidesToScroll: 2
            }
          },
          {
            breakpoint: 481,
            settings: {
              slidesToShow: 1,
              slidesToScroll: 1
            }
          }
        ]
      });

    });
  });

  //
  // Search
  //

  // ## Hide empty facets
  //
  // A patch for this exists, but does not work on the initial page load if
  // facets aren't passed in the URL.
  //
  // Issue: https://www.drupal.org/project/facets/issues/2984465#comment-12882752
  // Partially working patch: https://www.drupal.org/files/issues/2018-12-05/2984465-19.patch
  //
  if (typeof Drupal != "undefined") {
    Drupal.behaviors.facetsEditForm = {
      attach: function (context, settings) {
        // if the .block-facets wrapper contains .facet-hide-when-empty somewhere,
        // hide the parent.
        $('.block-facets').each(function () {
          var $this = $(this);
          // if ($this.find('.facet-hide-when-empty').length) {
          if ($this.find('.facet-empty').length) {
            $this.hide();
          }
        });
      }
    };
  }

  // ## Search exposed form
  $(function(){
    $('.block-system-main-block').each(function(){
      var $container = $(this);
      $container.on('change', '.usda-search-results select[name=sort_by]', function(){
        var $button = $container.find('.usda-search-results .form-actions input[type=submit]');
        if ($button.length > 0) $button.click();
      });
    });
  });

  // ## Open external URLs in new tab
  $(function(){
    var documentHost = document.location.host;
    var nonExternalHosts = [
      'public.govdelivery.com'
    ];

    if(window.self === window.top) { // Do not remove for iframe
      $('a[target="_blank"]').removeAttr('target');
    }

      function isLinkExternal(link_element) {
      // The link is external if:
      return link_element.host
        && link_element.host !== documentHost // 1. not current host
        && !/\.gov$/.test(link_element.host) // 2. not ending with .gov
        && $.inArray(link_element.host, nonExternalHosts) === -1 // 3. not on our inclusion list
      ;
    }

    function noWrapFirstWord(link) {
      let node = link.contents().filter(function () { return this.nodeType === 3 }).first(),
          text = node.text(),
          firstWord = text.split(" ", 1).join(" ")
      ;


      if (!node.length) {
        return;
      }

      node[0].nodeValue = text.slice(firstWord.length);
      node.before(`<span class="whitespace-nowrap"><span class="icon icon-new-tab external-link"></span>${firstWord}</span>`);
    }

    $('.uswds-main-content-wrapper a').not(':has(div,img), .usa-link-no-external-link-icon').each(function() {
      if (isLinkExternal(this)) {
        noWrapFirstWord($(this));
      }
    });
  });

  // Add data-column-header attribute to table cells
  $(function(){
    $('table').each(function(){
      const $table = $(this);
      const $headers = $table.find('th');
      const $rows = $table.find('tbody tr');

      $rows.each(function(){
        const $row = $(this);
        $cells = $row.find('td');
        $cells.each(function(i){
          $cell = $(this);
          $header = $headers.eq(i);
          if ($header.has('a').length) {
            $header.find('a span').remove();
          };

          const columnText = $header.text().trim();
          $cell.attr('data-column-header', columnText);
        })
      })

    });
  });

  // Add role attributes to tables
  // This is need for screen readers to read the table correctly when the mobile styles are applied because the mobile styles break the table into a list of blocks.
  $(function(){
    $('table').attr('role', 'table');
    $('caption').attr('role', 'caption');
    $('thead, tbody, tfoot').attr('role', 'rowgroup');
    $('tr').attr('role', 'row');
    $('td').attr('role', 'cell');
    $('th').attr('role', 'columnheader');
    $('th[scope=row]').attr('role', 'rowheader');
  });

  $(function(){
    const jumplinksMobile   = document.getElementById('systematic-review-question-nav-mobile');
    const jumplinksDesktop  = document.getElementById('systematic-review-question-nav-desktop');

    const scrollOptions = {
      behavior: window.matchMedia('(prefers-reduced-motion: reduce)').matches ? 'auto' : 'smooth'
    }

    if (jumplinksMobile ) {
      const content = document.getElementById('systematic-review-question-page-content');
      const menuWrapper = document.getElementById('systematic-review-question-nav-mobile');
      const details = jumplinksMobile.querySelector('details');
      const summary = details.querySelector('summary');

      let lastScrollY = window.scrollY;
      let ticking = false;
      let ignoreScroll = false;

      const links = jumplinksMobile.querySelectorAll('a[href^="#"]');
      links.forEach(link => {
        link.addEventListener('click', function(e){
          e.preventDefault();

          const hash    = e.target.hash;
          const target  = document.querySelector(hash);

          if (!target) return;

          details.open = false;

          window.history.replaceState(null, '', hash);

          window.setTimeout( () => {
              let menuHeight = menuWrapper.getBoundingClientRect().height + 20;
              content.style.setProperty('--offsetTop', menuHeight + 'px');
              target.scrollIntoView(scrollOptions);
          }, 0);
        });
      });

      // Detect sticky at top
      function isStickyAtTop(elem) {
        const rect = elem.getBoundingClientRect();
        const style = window.getComputedStyle(elem);
        return (
          Math.abs(rect.top) < 2 &&
          (style.position === 'sticky' || style.position === '-webkit-sticky')
        );
      }

      // Scroll handler
      function onScroll() {
        if (ignoreScroll) return;
        if (!details.open) return;

        if (window.scrollY > lastScrollY && isStickyAtTop(jumplinksMobile)) {
          details.open = false;
          jumplinksMobile.scrollIntoView({ block: "start" });
        }

        lastScrollY = window.scrollY;
      }

      // Because opening the <details> triggers a layout change and scroll event
      // we need to add a flag to skip the scroll even and revert it shortly after
      summary.addEventListener('click', () => {
        // Only set ignore if we're about to open it
        if (!details.open) {
          details.open = false;
          ignoreScroll = true;
          setTimeout(() => {
            ignoreScroll = false;
          }, 300);
        }
      });

      window.addEventListener('scroll', () => {

        if (isStickyAtTop(jumplinksMobile)) {
          jumplinksMobile.classList.add('isSticky');
        } else {
          jumplinksMobile.classList.remove('isSticky');
        }

        if (!ticking) {
          window.requestAnimationFrame(() => {
            onScroll();
            ticking = false;
          });
          ticking = true;
        }
      });
    }

    if (jumplinksDesktop) {
      const links = jumplinksDesktop.querySelectorAll('a[href^="#"]');
      links.forEach(link => {
        link.addEventListener('click', function(e){
          e.preventDefault();
          const hash    = e.target.hash;
          const target  = document.querySelector(hash);

          if (!target) return;

          target.scrollIntoView(scrollOptions);
        });
      });

      window.addEventListener('scroll', function () {
        let currentHeader = null;

        links.forEach(link => {
          const hash = link.getAttribute('href')
          const header = document.querySelector(hash);

          const rect = header.getBoundingClientRect();

          if (rect.top <= 0) {
            currentHeader = link;
          }
        });


        links.forEach(link => {
          if (link === currentHeader) {
            link.classList.add('current');
          } else {
            link.classList.remove('current');
          }
        });

      });
    }

  });

})(jQuery);
