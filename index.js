const path = require('path');

/**
 * @function
 * @param {string} BeatmapPath 
 * @example
 * noppai(__dirname + "The big Black.osu")
 */
function noppai(BeatmapPath) {
  this.nop = require('bindings')('noppai')(path.join(BeatmapPath));
  return {
    /**
     * @function
     * @returns {PP} Calculated PP
     */
    CalculatePP: this.nop.CalculatePP,
    /**
     * @function
     * @returns {Stars} Calculated Stars
     */
    CalculateStars: this.nop.CalculateStars
  };

  /**
   * @inner CalculatePP
   * @type {Object}
   */
  const PP = {
    /**
     * @extends PP
     * @type {number}
     */
    total,
    /**
     * @extends PP
     * @type {number}
     */
    aim,
    /**
     * @extends PP
     * @type {number}
     */
    speed,
    /**
     * @extends PP
     * @type {number}
     */
    acc
  }
}
module.exports = noppai;