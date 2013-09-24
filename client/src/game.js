var PathSmoothing = function(context, smoothness) {
  this.context = context;
  this.smoothness = smoothness;
  this.prevX = 0;
  this.prevY = 0;
  this.first = true;
};

PathSmoothing.prototype.moveTo = function(x, y) {
  this.first = true;
  this.prevX = x;
  this.prevY = y;
  this.context.moveTo(x, y);
};

PathSmoothing.prototype.lineTo = function(x, y) {
  var midX = (x + this.prevX) / 2.0;
  var midY = (y + this.prevY) / 2.0;

  var invSmoothness = 1-this.smoothness;
  var cpX = this.prevX;
  var cpY = this.prevY;

  var curveEndX, curveEndY;

  curveEndX = (this.smoothness * midX + invSmoothness * cpX);
  curveEndY = (this.smoothness * midY + invSmoothness * cpY);

  if (!this.first) {
    this.context.quadraticCurveTo(cpX, cpY, curveEndX, curveEndY);
  }

  var nextCurveStartX = (this.smoothness * midX + invSmoothness * x);
  var nextCurveStartY = (this.smoothness * midY + invSmoothness * y);

  this.context.lineTo(nextCurveStartX, nextCurveStartY);

  this.prevX = x;
  this.prevY = y;

  this.first = false;
};

PathSmoothing.prototype.endPath = function() {
  this.context.lineTo(this.prevX, this.prevY);
};

var Game = {
  init: function() {
    var icon_width = 48;
    var icon_height = 48;

    var $container = $('<div>').addClass('dracula-container');
    var $sea = $('<div>').addClass('dracula-sea');
    var $map = $('<div>').addClass('dracula-map');
    var $roads = $('<canvas>').addClass('dracula-canvas');
    var $railways = $('<canvas>').addClass('dracula-canvas');
    var $border = $('<div>').addClass('dracula-border');
    var $cities = $('<div>').addClass('dracula-cities');

    var $dracula = $('<div>').addClass('dracula-player dracula');
    var $godalming = $('<div>').addClass('dracula-player godalming');
    var $seward = $('<div>').addClass('dracula-player seward');
    var $helsing = $('<div>').addClass('dracula-player helsing');
    var $harker = $('<div>').addClass('dracula-player harker');

    $cities.append($roads).append($railways)

    $container 
      .append($sea)
      .append($map)
      .append($border)
      .append($cities)
      .append($godalming).append($seward).append($helsing).append($harker)
      .append($dracula)
      .appendTo($('body'));

    $roads[0].width = $map.width();
    $railways[0].width = $map.width();
    $roads[0].height = $map.height();
    $railways[0].height = $map.height();

    $dracula.css({
      top: '80px',
      left: '1700px'
    }).draggable().text('Dracula');

    $godalming.css({
      top: '80px',
      left: '1450px'
    }).draggable().text('Lord Godalming');

    $seward.css({
      top: '80px',
      left: '1500px'
    }).draggable().text('Dr Seward');

    $helsing.css({
      top: '80px',
      left: '1550px'
    }).draggable().text('Van Helsing');

    $harker.css({
      top: '80px',
      left: '1600px'
    }).draggable().text('Mina Harker');

    var roadCtx = $roads[0].getContext('2d');
    var railCtx = $roads[0].getContext('2d');
    var roads = new PathSmoothing(roadCtx, 1.0);
    var rail  = new PathSmoothing(railCtx, 1.0);

    $.each(Routes, function(route, coords) {
      if (route.substr(0, 4) === 'road') {
        roadCtx.lineWidth = 3;
        roadCtx.strokeStyle = 'rgba(50,20,0,0.35)'; 
        roadCtx.beginPath();
        $.each(coords, function(i, coord) {
          coord.x = parseFloat(coord.x);
          coord.y = parseFloat(coord.y);

          if (i === 0) {
            roads.moveTo(coord.x, coord.y);
          } else {
            roads.lineTo(coord.x, coord.y);
          }
        });
        roads.endPath();
        roadCtx.stroke();
      } else if (route.substr(0, 4) === 'rail') {
        railCtx.save();

        railCtx.lineWidth = 4;
        railCtx.strokeStyle = 'rgba(0,0,0,0.45)';
        railCtx.beginPath();
        $.each(coords, function(i, coord) {
          coord.x = parseFloat(coord.x);
          coord.y = parseFloat(coord.y);

          if (i === 0) {
            rail.moveTo(coord.x, coord.y);
          } else {
            rail.lineTo(coord.x, coord.y);
          }
        });
        rail.endPath();
        railCtx.stroke();

        railCtx.globalCompositeOperation = 'destination-out';

        railCtx.lineWidth = 2;
        railCtx.setLineDash && railCtx.setLineDash([4,1]);
        railCtx.strokeStyle = 'white';
        railCtx.beginPath();
        $.each(coords, function(i, coord) {
          coord.x = parseFloat(coord.x);
          coord.y = parseFloat(coord.y);

          if (i === 0) {
            rail.moveTo(coord.x, coord.y);
          } else {
            rail.lineTo(coord.x, coord.y);
          }
        });
        rail.endPath();

        railCtx.stroke();
        
        railCtx.restore();
      }

    });

    $.each(Cities, function(cityCode, city) {
      var eltClass;

      var textOffset = 32;
      if (city.icon === 'small') {
        textOffset = 24;
      }

      if (city.icon === 'large' || city.icon === 'small') {
        if (city.port === 'yes') {
          eltClass = 'port_' + city.icon;
        } else {
          eltClass = 'city_' + city.icon;
        }
      } else {
        eltClass = city.icon;
      }

      var left, top;

      top  = parseFloat(city.y) - icon_height/2;
      left = parseFloat(city.x) - icon_height/2;

      var $city = $('<div>')
        .addClass(eltClass)
        .css({
          position: 'absolute',
          top: top,
          left: left
        });

      $cities.append($city);

      var textAngle = parseFloat(city.text_rot) * Math.PI / 180;

      top = parseFloat(city.y) + Math.sin(textAngle) * textOffset;
      left = parseFloat(city.x) + Math.cos(textAngle) * textOffset;

      var $text = $('<span>')
        .css({
          position: 'absolute',
          top: top,
          left: left
        })
        .text(city.name)
        .addClass('city_text');

      $cities.append($text);

      left -= $text.width()/2;
      top  -= 8;

      $text.css('left', left);
      $text.css('top', top);

      $city.on('mouseenter', function() {
        $text.addClass('active');
      }).on('mouseleave', function() {
        $text.removeClass('active');
      });

      $text.on('mouseenter', function() {
        $text.addClass('active');
      }).on('mouseleave', function() {
        $text.removeClass('active');
      });

    });

  },
};

Game.init();